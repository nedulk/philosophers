/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:23:29 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/28 17:11:24 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data *data;
	int	id;
	int eat_count;
	pthread_mutex_t lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t *l_fork;
	
}	t_philo;

typedef struct s_data
{
	t_philo *philosophe;
	pthread_t *thread_id;
	int	nb_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meal;
	pthread_mutex_t *forks;
	pthread_mutex_t	lock;
	pthread_mutex_t message;
	
}	t_data;

int	ft_atoi(char *str);

#endif
