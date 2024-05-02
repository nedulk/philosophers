/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:41:06 by kprigent          #+#    #+#             */
/*   Updated: 2024/05/02 17:45:46 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death_message(t_philo *data, int id)
{
	pthread_mutex_lock(&data->time_mutex);
	printf(RED "%ld %d died\n" RESET,
		(data->stop_time - data->start_time), id + 1);
	pthread_mutex_unlock(&data->philo_died);
	pthread_mutex_unlock(&data->time_mutex);
}

void	set_philo_died(t_philo *data)
{
	pthread_mutex_lock(&data->philo_died);
	data->one_philo_died = 1;
	pthread_mutex_unlock(&data->philo_died);
}

int	check_initial_death(t_philo *data, int id, int stop_m_start)
{
	pthread_mutex_lock(&data->last_meal_mutex[id]);
	if (data->last_meal_time[id] == 0 && (stop_m_start >= data->time_to_die))
	{
		pthread_mutex_lock(&data->philo_died);
		if (data->one_philo_died == 0)
		{
			data->one_philo_died = 1;
			print_death_message(data, id);
		}
		else
			pthread_mutex_unlock(&data->philo_died);
		set_philo_died(data);
		pthread_mutex_unlock(&data->last_meal_mutex[id]);
		pthread_mutex_unlock(&data->check_death);
		return (1);
	}
	pthread_mutex_unlock(&data->last_meal_mutex[id]);
	return (0);
}

int	check_later_death(t_philo *data, int id)
{
	pthread_mutex_lock(&data->last_meal_mutex[id]);
	pthread_mutex_lock(&data->time_mutex);
	if ((data->last_meal_time[id] != 0
			&& ((data->stop_time - data->last_meal_time[id])
				>= data->time_to_die)))
	{
		pthread_mutex_unlock(&data->time_mutex);
		pthread_mutex_lock(&data->philo_died);
		if (data->one_philo_died == 0)
		{
			data->one_philo_died = 1;
			print_death_message(data, id);
		}
		else
			pthread_mutex_unlock(&data->philo_died);
		set_philo_died(data);
		pthread_mutex_unlock(&data->check_death);
		pthread_mutex_unlock(&data->last_meal_mutex[id]);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->time_mutex);
	pthread_mutex_unlock(&data->last_meal_mutex[id]);
	return (0);
}

int	check_death_philo(t_philo *data, int id)
{
	int	stop_m_start;

	pthread_mutex_lock(&data->check_death);
	pthread_mutex_lock(&data->time_mutex);
	data->stop_time = get_time();
	pthread_mutex_unlock(&data->time_mutex);
	pthread_mutex_lock(&data->time_mutex);
	stop_m_start = data->stop_time - data->start_time;
	pthread_mutex_unlock(&data->time_mutex);
	if (check_initial_death(data, id, stop_m_start) == 1)
		return (1);
	pthread_mutex_lock(&data->time_mutex);
	stop_m_start = data->stop_time - data->start_time;
	pthread_mutex_unlock(&data->time_mutex);
	if (check_later_death(data, id) == 1)
		return (1);
	pthread_mutex_unlock(&data->check_death);
	return (0);
}
