/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:34:28 by kleden            #+#    #+#             */
/*   Updated: 2024/01/30 18:15:19 by kprigent         ###   ########.fr       */
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

void take_forks(t_philo *data, int id)
{
    pthread_mutex_lock(&data->forks[id]);
	data->stop_time = get_time();
    printf("%ld %d has taken a fork\n", (data->stop_time - data->start_time), id);
	pthread_mutex_lock(&data->forks[(id + 1) % (data->nb_of_philosophers - 1)]);
	data->stop_time = get_time();
	printf("%ld %d has taken a fork\n", (data->stop_time - data->start_time), id);
}

void	drop_forks(t_philo *data, int id)
{
	pthread_mutex_unlock(&data->forks[id]);
	pthread_mutex_unlock(&data->forks[(id + 1) % (data->nb_of_philosophers - 1)]);
	data->stop_time = get_time();
    printf("%ld %d is sleeping\n", (data->stop_time - data->start_time), id);
	usleep(data->time_to_sleep * 1000);
}


void* eat(void *arg)
{
	t_philo *data = (t_philo *)arg;
	static int f = 0;
	int id;

	pthread_mutex_lock(&data->lock_id);
	if (data->id == data->nb_of_philosophers)
	{
		data->id = 0;
		f = 0;
	}
	if (f == 1)
		id = data->id++;
	else
	{
		id = data->id;
		f = 1;
	}
	pthread_mutex_unlock(&data->lock_id);
	take_forks(data, id);
	pthread_mutex_lock(&data->philo_lock[id]);
	data->stop_time = get_time();
	printf("%ld %d is eating\n", (data->stop_time - data->start_time), id);
	data->eat_count[id]++;
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->philo_lock[id]);
	drop_forks(data, id);
	data->stop_time = get_time();
	printf("%ld %d is thinking\n", (data->stop_time - data->start_time), id);
	return (NULL);
}