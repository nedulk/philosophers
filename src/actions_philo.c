/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:34:28 by kleden            #+#    #+#             */
/*   Updated: 2024/04/25 15:28:25 by kprigent         ###   ########.fr       */
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
	if (data->nb_of_philosophers == 1)
		return ;
    pthread_mutex_lock(&data->forks[id]);
	data->stop_time = get_time();
	if (data->one_philo_died == 0)
    	printf("%ld %d has taken a fork\n", (data->stop_time - data->start_time), id);
	pthread_mutex_lock(&data->forks[(id + 1) % (data->nb_of_philosophers)]);
	data->stop_time = get_time();
	if (data->one_philo_died == 0)
		printf("%ld %d has taken a fork\n", (data->stop_time - data->start_time), id);
}

void	drop_forks(t_philo *data, int id)
{
	pthread_mutex_unlock(&data->forks[id]);
	pthread_mutex_unlock(&data->forks[(id + 1) % (data->nb_of_philosophers)]);
	data->stop_time = get_time();
	if (data->one_philo_died == 0)
    {	
		printf("%ld %d is sleeping\n", (data->stop_time - data->start_time), id);
		usleep(data->time_to_sleep * 1000);
	}
}

int check_death_philo(t_philo *data, int id)
{
	int i;

	i = 0;
	pthread_mutex_lock(&data->check_death);
	data->stop_time = get_time();
	if (data->last_meal_time[id] == 0 && (data->stop_time - data->start_time >= data->time_to_die))
	{
		if (data->one_philo_died == 0)
			printf(RED "%ld %d died\n" RESET, (data->stop_time - data->start_time), id);
		data->one_philo_died = 1;
		pthread_mutex_unlock(&data->check_death);
		return (1);
	}
	else if ((data->last_meal_time[id] != 0 && ((data->stop_time - data->last_meal_time[id]) >= data->time_to_die)))
	{
		if (data->one_philo_died == 0)
			printf(RED "%ld %d died\n" RESET, (data->stop_time - data->start_time), id);
		data->one_philo_died = 1;
		pthread_mutex_unlock(&data->check_death);
		return (1);
	}
	pthread_mutex_unlock(&data->check_death);
	return (0);
}

void* start_dinner(void *arg, int id)
{
	t_philo *data = (t_philo *)arg;

	take_forks(data, id);
	pthread_mutex_lock(&data->philo_lock[id]);
	data->stop_time = get_time();
	if (data->one_philo_died == 0)
		printf("%ld %d is eating\n", (data->stop_time - data->start_time), id);
	data->eat_count[id]++;
	data->last_meal_time[id] = get_time();
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->philo_lock[id]);
	drop_forks(data, id);
	data->stop_time = get_time();
	if (data->one_philo_died == 0)
		printf("%ld %d is thinking\n", (data->stop_time - data->start_time), id);
	return (NULL);
}
