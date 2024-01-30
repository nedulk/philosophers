/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:23:29 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/30 16:37:25 by kprigent         ###   ########.fr       */
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
	int				id;
	int				nb_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meal;
	long int		start_time;
	long int		stop_time;
	int*			eat_count;
	pthread_t		*philo;
	pthread_mutex_t	print;
	pthread_mutex_t sleep;
	pthread_mutex_t	*philo_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_id;
	
}	t_philo;

int			ft_atoi(char *str);
void*		eat(void *arg);
long int	get_time(void);

#endif
