/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:47:46 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/26 13:56:27 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int every_philo_ate(t_philo *data, int id)
{
	pthread_mutex_lock(&data->eat_count_mutex);
	if (data->eat_count[id] > data->number_of_meal)
	{
		pthread_mutex_unlock(&data->eat_count_mutex);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->eat_count_mutex);
	return (0);
}
void *death_check_routine(void* arg)
{
	t_philo *data = (t_philo *)arg;
	int id;

	id = 0;
	while (1)
	{
		if (check_death_philo(data, id) == 1)
		{
			return (NULL);
		}
		id = (id + 1) % data->nb_of_philosophers;
	}
	return (NULL);
}

void *eat_count_check_routine(void* arg)
{
	t_philo *data = (t_philo *)arg;
	int id;

	id = 0;
	while (1)
	{
		pthread_mutex_lock(&data->philo_died);
		if (data->one_philo_died == 1)
		{
			pthread_mutex_unlock(&data->philo_died);
			return (NULL);
		}
		else
			pthread_mutex_unlock(&data->philo_died);
		if (data->number_of_meal != -1 && every_philo_ate(data, id) == 1)
		{
			printf(GREEN "Everyone ate enough\n" RESET);
			exit(0);
		}
		id = (id + 1) % data->nb_of_philosophers;
	}
	return (NULL);
}

void *philo_routine(void* arg)
{
	t_philo_data *philo_data = (t_philo_data *)arg;
	t_philo *data = philo_data->data;
	int id = philo_data->id;

	while (1)
	{
		if (id % 2 == 0)
			usleep(100);
		pthread_mutex_lock(&data->philo_died);
		if (data->one_philo_died == 1)
		{
			pthread_mutex_unlock(&data->philo_died);	
			return (NULL);
		}
		pthread_mutex_unlock(&data->philo_died);
		start_dinner(data, id);
	}
	return (NULL);
}

void ft_join(t_philo *data, pthread_t death_check_thread, pthread_t eat_count_check_thread)
{
	int id = 0;
	void *return_value;
	
	while (id < data->nb_of_philosophers)
	{
		pthread_join(data->philo[id], &return_value);
		id++;
	}
	if (data->number_of_meal != -1)
		pthread_join(eat_count_check_thread, &return_value);
	pthread_join(death_check_thread, &return_value);
}
