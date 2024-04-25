/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:34:28 by kleden            #+#    #+#             */
/*   Updated: 2024/04/25 19:44:33 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	// seconde -> millisecondes  puis convertit les microsecondes -> milliseondes
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	take_forks(t_philo *data, int id)
{
    int next_id = (id + 1) % (data->nb_of_philosophers);

    if (id < next_id) {
        pthread_mutex_lock(&data->forks[id]);
        if (data->nb_of_philosophers == 1)
        {
            pthread_mutex_unlock(&data->forks[id]);
            return (1);
        }
        pthread_mutex_lock(&data->forks[next_id]);
    } else {
        pthread_mutex_lock(&data->forks[next_id]);
        if (data->nb_of_philosophers == 1)
        {
            pthread_mutex_unlock(&data->forks[next_id]);
            return (1);
        }
        pthread_mutex_lock(&data->forks[id]);
    }

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

int check_death_philo(t_philo *data, int id)
{
	int i;
	int stop_m_start;

	i = 0;
	pthread_mutex_lock(&data->check_death);
	pthread_mutex_lock(&data->time_mutex);
	data->stop_time = get_time();
	pthread_mutex_unlock(&data->time_mutex);
	pthread_mutex_lock(&data->time_mutex);
	stop_m_start = data->stop_time - data->start_time;
	pthread_mutex_unlock(&data->time_mutex);
	pthread_mutex_lock(&data->last_meal_mutex[id]);
	if (data->last_meal_time[id] == 0 && (stop_m_start >= data->time_to_die))
	{
		pthread_mutex_lock(&data->philo_died);	
		if (data->one_philo_died == 0)
		{	
			pthread_mutex_unlock(&data->philo_died);
			pthread_mutex_lock(&data->time_mutex);
			printf(RED "%ld %d died\n" RESET, (data->stop_time - data->start_time), id);
			pthread_mutex_unlock(&data->time_mutex);
		}
		else
			pthread_mutex_unlock(&data->philo_died);
		pthread_mutex_lock(&data->philo_died);
		data->one_philo_died = 1;
		pthread_mutex_unlock(&data->philo_died);
		pthread_mutex_unlock(&data->last_meal_mutex[id]);
		pthread_mutex_unlock(&data->check_death);
		return (1);
	}
	pthread_mutex_unlock(&data->last_meal_mutex[id]);
	pthread_mutex_lock(&data->time_mutex);
	stop_m_start = data->stop_time - data->start_time;
	pthread_mutex_unlock(&data->time_mutex);
	
	pthread_mutex_lock(&data->last_meal_mutex[id]);
	if ((data->last_meal_time[id] != 0 && ((data->stop_time - data->last_meal_time[id]) >= data->time_to_die)))
	{
		pthread_mutex_lock(&data->philo_died);
		if (data->one_philo_died == 0)
		{
			pthread_mutex_unlock(&data->philo_died);
			pthread_mutex_lock(&data->time_mutex);
			printf(RED "%ld %d died\n" RESET, (data->stop_time - data->start_time), id);
			pthread_mutex_unlock(&data->time_mutex);
		}
		else
			pthread_mutex_unlock(&data->philo_died);
		pthread_mutex_lock(&data->philo_died);
		data->one_philo_died = 1;
		pthread_mutex_unlock(&data->philo_died);
		pthread_mutex_unlock(&data->check_death);
		pthread_mutex_unlock(&data->last_meal_mutex[id]);
		return (1);
	}
	pthread_mutex_unlock(&data->last_meal_mutex[id]);
	pthread_mutex_unlock(&data->check_death);
	return (0);
}

void* start_dinner(void *arg, int id)
{
	t_philo *data = (t_philo *)arg;

	if (take_forks(data, id) == 1)
	{
		return (NULL);
	}
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
	drop_forks(data, id);
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
	return (NULL);
}
