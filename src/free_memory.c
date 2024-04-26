/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:04:58 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/26 17:05:22 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_memory(t_philo *data)
{
	int	id;

	id = 0;
	while (id < data->nb_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[id]);
		pthread_mutex_destroy(&data->philo_lock[id]);
		pthread_mutex_destroy(&data->last_meal_mutex[id]);
		id++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->sleep);
	pthread_mutex_destroy(&data->check_death);
	pthread_mutex_destroy(&data->time_mutex);
	pthread_mutex_destroy(&data->philo_died);
	pthread_mutex_destroy(&data->eat_count_mutex);
	free(data->last_meal_time);
	free(data->last_meal);
	free(data->philo);
	free(data->philo_lock);
	free(data->forks);
	free(data->last_meal_mutex);
	free(data->eat_count);
}
