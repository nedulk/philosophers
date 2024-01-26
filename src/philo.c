/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:17:57 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/26 17:53:04 by kprigent         ###   ########.fr       */
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

void	init_var(t_philo *ptr, char **argv)
{
	if (!ptr)
	{
		printf("ERROR\nMemory allocation failed\n");	
		exit(0);
	}
	ptr->numbers_of_philosophers = ft_atoi(argv[1]);
	ptr->time_to_die = ft_atoi(argv[2]);
	ptr->time_to_eat = ft_atoi(argv[3]);
	ptr->time_to_sleep = ft_atoi(argv [4]);
	ptr->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	ptr->mutex = malloc(sizeof(pthread_mutex_t) * ptr->numbers_of_philosophers);
	ptr->philosophe = malloc(sizeof(pthread_t) * ptr->numbers_of_philosophers);
	if (!ptr->mutex || !ptr->philosophe)
	{
		printf("ERROR\nMemory allocation failed\n");	
		exit(0);
	}
}

void	*action_philo(void *arg)
{
	t_philo *ptr;
	static long int stop_time = 0;
	
	ptr = (t_philo *)arg;
	//check si philo dead, faire une fonction pour check a chaque lancement de
	//action_philo
	//eating 
	
	pthread_mutex_lock(&ptr->mutex[ptr->id]);
	stop_time = get_time();
	printf("%ld %d has taken a fork\n", (stop_time - ptr->start_time), ptr->id);
	pthread_mutex_lock(&ptr->mutex[(ptr->id + 1) % ptr->numbers_of_philosophers]);
	stop_time = get_time();
	printf("%ld %d has taken a fork\n", (stop_time - ptr->start_time), ptr->id);
	printf("%ld %d is eating\n", (stop_time - ptr->start_time), ptr->id);
	usleep((ptr->time_to_eat * 1000));
	//sleeping
	pthread_mutex_unlock(&ptr->mutex[ptr->id]);
	pthread_mutex_unlock(&ptr->mutex[(ptr->id + 1) % ptr->numbers_of_philosophers]);
	
	stop_time = get_time();
	printf("%ld %d is sleeping\n", (stop_time - ptr->start_time), ptr->id);
	usleep(ptr->time_to_sleep * 1000);
	//thinking
	stop_time = get_time();
	printf("%ld %d is thinking\n", (stop_time - ptr->start_time), ptr->id);
	return (NULL);
}

void create_thread(t_philo *ptr)
{
	ptr->id = 0;
	while (ptr->id < ptr->numbers_of_philosophers)
	{
		pthread_create(&ptr->philosophe[ptr->id], NULL, action_philo, (void*)ptr);
		pthread_join(ptr->philosophe[ptr->id], NULL);
		ptr->id += 2;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*ptr;

	ptr = NULL;
	if (argc != 6)
	{
		printf("ERROR\nMissing arguments/too much arguments\n");
		exit(0);
	}
	ptr = malloc(sizeof(t_philo));
	init_var(ptr, argv);
	ptr->start_time = get_time();
	create_mutex(ptr);
	create_thread(ptr);
	return (0);
}
