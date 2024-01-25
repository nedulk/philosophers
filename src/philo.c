/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:17:57 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/26 00:19:11 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	

	ptr = (t_philo *)arg;
	//check si philo dead, faire une fonction pour check a chaque lancement de
	//action_philo
	//eating
	start = 
	pthread_mutex_lock(&ptr->mutex[ptr->id]);
	printf("Philosopher %d has taken a fork\n", ptr->id);
	pthread_mutex_lock(&ptr->mutex[(ptr->id + 1) % ptr->numbers_of_philosophers]);
	printf("Philosopher %d has taken a fork\n", ptr->id);
	printf("Philosopher %d is eating\n", ptr->id);
	usleep(ptr->time_to_eat);
	//sleeping
	pthread_mutex_unlock(&ptr->mutex[ptr->id]);
	pthread_mutex_unlock(&ptr->mutex[(ptr->id + 1) % ptr->numbers_of_philosophers]);
	printf("Philosopher %d is sleeping\n", ptr->id);
	usleep(ptr->time_to_sleep);
	//thinking
	printf("Philosopher %d is thinking\n", ptr->id);
	return (NULL);
}

long int	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	// seconde -> millisecondes  puis convertit les microsecondes -> milliseondes
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/*void ft_usleep(long int time_given)
{
	long int start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_given)
		usleep(time_given / 10);
}*/

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
	ptr->id = 0;
	while (ptr->id < ptr->numbers_of_philosophers)
	{
		pthread_mutex_init(&ptr->mutex[ptr->id], NULL);
		ptr->id += 1;
	}
	ptr->id = 0;
	while (ptr->id < ptr->numbers_of_philosophers)
	{
		pthread_create(&ptr->philosophe[ptr->id], NULL, action_philo, (void*)ptr);
		ptr->id += 1;
	}
	return (0);
}
