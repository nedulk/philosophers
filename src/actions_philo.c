/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:34:28 by kleden            #+#    #+#             */
/*   Updated: 2024/01/28 16:59:25 by kprigent         ###   ########.fr       */
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

void take_forks(t_philo *philosophe)
{
    pthread_mutex_lock(philosophe->l_fork);
    printf("%ld %d has taken a fork\n", stoptime, id);
	pthread_mutex_lock(philosophe->r_fork);
	printf("%ld %d has taken a fork\n", stoptime, id);
}

void	drop_forks(t_philo *philosophe)
{
	pthread_mutex_unlock(philosophe->l_fork);
	pthread_mutex_unlock(philosophe->r_fork);
    printf("%ld %d is sleeping\n", stoptime, id);
	usleep(philosophe->data->time_to_sleep);
}

void	eat(t_philo *philosophe)
{
	take_forks(philosohe);
	pthread_mutex_lock(&philosophe->lock);
	prtintf("%ld %d is eating\n", stoptime, id);
	philosophe->eat_count++;
	ft_usleep(philosophe->data->eat_time);
	pthread_mutex_unlock(&philosophe->lock);
	drop_forks(philosohe);
}