/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:23:29 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/26 17:05:54 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define RESET   "\x1B[0m"
# define RED     "\x1B[31m"
# define GREEN   "\x1B[32m"
# define YELLOW  "\x1B[33m"
# define BLUE    "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN    "\x1B[36m"
# define WHITE   "\x1B[37m"

# define R   "\x1B[31m"
# define G   "\x1B[32m"
# define Y   "\x1B[33m"
# define RESET "\x1B[0m"

typedef struct s_philo
{
	int				id;
	int				nb_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meal;
	int				one_philo_died;
	long int		start_time;
	long int		stop_time;
	int				*eat_count;
	int				*last_meal;
	long int		*last_meal_time;
	pthread_t		*philo;
	pthread_mutex_t	check_death;
	pthread_mutex_t	philo_died;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	*last_meal_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	sleep;
	pthread_mutex_t	*philo_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_id;

}	t_philo;

typedef struct s_philo_data
{
	t_philo	*data;
	int		id;

}	t_philo_data;

///INITIALISATION
void		init_forks_and_locks(t_philo *data);
void		init_arrays(t_philo *data);
void		allocate_memory(t_philo *data);
void		init_mutexes(t_philo *data);
void		init_vars(t_philo *data, char **argv);

///ROUTINE
void		*death_check_routine(void *arg);
void		*eat_count_check_routine(void *arg);
void		*philo_routine(void *arg);
void		*start_dinner(void *arg, int id);
int			check_death_philo(t_philo *data, int id);
int			take_forks(t_philo *data, int id);
void		drop_forks(t_philo *data, int id);
void		ft_join(t_philo *data, pthread_t death_check_thread,
				pthread_t eat_count_check_thread);

long int	ft_atoi(const char *str);
long int	get_time(void);
char		*ft_strdup(const char *src);
int			ft_strlen(char *str);
int			parsing(int argc, char **argv);
void		start_routine(t_philo *data);
int			check_death_philo(t_philo *data, int id);
void		*start_dinner(void *arg, int id);
void		free_memory(t_philo *data);

#endif
