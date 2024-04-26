/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:15:45 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/26 14:33:28 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_fork_message(t_philo *data, int id)
{
    pthread_mutex_lock(&data->time_mutex);
    data->stop_time = get_time();
    pthread_mutex_unlock(&data->time_mutex);

    pthread_mutex_lock(&data->philo_died);
    if (data->one_philo_died == 0)
    {
        pthread_mutex_lock(&data->time_mutex);
        printf("%ld %d has taken a fork\n", (data->stop_time - data->start_time), id);
        pthread_mutex_unlock(&data->time_mutex);
    }
    pthread_mutex_unlock(&data->philo_died);
}

int take_forks(t_philo *data, int id)
{
    if (id < ((id + 1) % (data->nb_of_philosophers))) 
    {
        pthread_mutex_lock(&data->forks[id]);
        if (data->nb_of_philosophers == 1)
        {
            pthread_mutex_unlock(&data->forks[id]);
            return (1);
        }
        pthread_mutex_lock(&data->forks[(id + 1) % (data->nb_of_philosophers)]);
    } 
    else 
    {
        pthread_mutex_lock(&data->forks[(id + 1) % (data->nb_of_philosophers)]);
        if (data->nb_of_philosophers == 1)
        {
            pthread_mutex_unlock(&data->forks[(id + 1) % (data->nb_of_philosophers)]);
            return (1);
        }
        pthread_mutex_lock(&data->forks[id]);
    }
    print_fork_message(data, id);
    print_fork_message(data, id);
    return (0);
}

void	drop_forks(t_philo *data, int id)
{
	pthread_mutex_unlock(&data->forks[id]);
	pthread_mutex_unlock(&data->forks[(id + 1) % (data->nb_of_philosophers)]);
	pthread_mutex_lock(&data->time_mutex);
	data->stop_time = get_time();
	pthread_mutex_unlock(&data->time_mutex);
	pthread_mutex_lock(&data->philo_died);
	if (data->one_philo_died == 0)
    {	
		pthread_mutex_unlock(&data->philo_died);
		pthread_mutex_lock(&data->time_mutex);
		printf("%ld %d is sleeping\n", (data->stop_time - data->start_time), id);
		pthread_mutex_unlock(&data->time_mutex);
		usleep(data->time_to_sleep * 1000);
	}
	else
		pthread_mutex_unlock(&data->philo_died);
}
