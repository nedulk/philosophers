/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:47:46 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/27 12:25:12 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	every_philo_ate(t_philo *data)
{
	int	id;

	pthread_mutex_lock(&data->eat_count_mutex);
	id = 0;
	while (id < data->nb_of_philosophers)
	{
		if (data->eat_count[id] <= data->number_of_meal)
		{
			pthread_mutex_unlock(&data->eat_count_mutex);
			return (0);
		}
		id++;
	}
	pthread_mutex_unlock(&data->eat_count_mutex);
	return (1);
}

void	*death_check_routine(void *arg)
{
	t_philo	*data;
	int		id;

	id = 0;
	data = (t_philo *)arg;
	while (1)
	{
		usleep(100);
		if (check_death_philo(data, id) == 1)
			return (NULL);
		id = (id + 1) % data->nb_of_philosophers;
	}
	return (NULL);
}

void	*eat_count_check_routine(void *arg)
{
	t_philo	*data;
	int		id;

	id = 0;
	data = (t_philo *)arg;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&data->philo_died);
		if (data->one_philo_died == 1)
		{
			pthread_mutex_unlock(&data->philo_died);
			return (NULL);
		}
		else
			pthread_mutex_unlock(&data->philo_died);
		if (data->number_of_meal != -1 && every_philo_ate(data) == 1)
		{
			printf(GREEN "Everyone ate enough\n" RESET);
			data->one_philo_died = 1;
			return (NULL);
		}
		id = (id + 1) % data->nb_of_philosophers;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo_data	*philo_data;
	t_philo			*data;
	int				id;

	philo_data = (t_philo_data *)arg;
	data = philo_data->data;
	id = philo_data->id;
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

void	ft_join(t_philo *data, pthread_t death_check_thread,
	pthread_t eat_count_check_thread)
{
	int		id;
	void	*return_value;

	id = 0;
	while (id < data->nb_of_philosophers)
	{
		pthread_join(data->philo[id], &return_value);
		id++;
	}
	if (data->number_of_meal != -1)
		pthread_join(eat_count_check_thread, &return_value);
	pthread_join(death_check_thread, &return_value);
}
