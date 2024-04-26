/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:34:28 by kleden            #+#    #+#             */
/*   Updated: 2024/04/26 14:15:57 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *data, int id)
{
    pthread_mutex_lock(&data->philo_lock[id]);
    pthread_mutex_lock(&data->time_mutex);
    data->stop_time = get_time();
    pthread_mutex_unlock(&data->time_mutex);
    pthread_mutex_lock(&data->philo_died);
    if (data->one_philo_died == 0)
    {
        pthread_mutex_unlock(&data->philo_died);
        pthread_mutex_lock(&data->time_mutex);
        printf("%ld %d is eating\n", (data->stop_time - data->start_time), id);
        pthread_mutex_unlock(&data->time_mutex);
    }
    else
        pthread_mutex_unlock(&data->philo_died);
    pthread_mutex_lock(&data->eat_count_mutex);
    data->eat_count[id]++;
    pthread_mutex_unlock(&data->eat_count_mutex);
    pthread_mutex_lock(&data->last_meal_mutex[id]);
    data->last_meal_time[id] = get_time();
    pthread_mutex_unlock(&data->last_meal_mutex[id]);
    usleep(data->time_to_eat * 1000);
    pthread_mutex_unlock(&data->philo_lock[id]);
}

void think(t_philo *data, int id)
{
    pthread_mutex_lock(&data->time_mutex);
    data->stop_time = get_time();
    pthread_mutex_unlock(&data->time_mutex);
    pthread_mutex_lock(&data->philo_died);
    if (data->one_philo_died == 0)
    {
        pthread_mutex_unlock(&data->philo_died);
        pthread_mutex_lock(&data->time_mutex);
        printf("%ld %d is thinking\n", (data->stop_time - data->start_time), id);
        pthread_mutex_unlock(&data->time_mutex);
    }
    else
        pthread_mutex_unlock(&data->philo_died);
}

void* start_dinner(void *arg, int id)
{
    t_philo *data = (t_philo *)arg;
    
    if (take_forks(data, id) == 1)
    {
        return (NULL);
    }
    eat(data, id);
    drop_forks(data, id);
    think(data, id);
    return (NULL);
}
