/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:17:57 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/25 19:08:27 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_var(t_philo *ptr, char **argv)
{
	ptr->numbers_of_philosophers = ft_atoi(argv[1]);
	ptr->time_to_die = ft_atoi(argv[2]);
	ptr->time_to_eat = ft_atoi(argv[3]);
	ptr->time_to_sleep = ft_atoi(argv [4]);
	ptr->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	ptr = malloc(sizeof(t_philo));
	ptr->mutex = malloc(sizeof(pthread_mutex_t) * ptr->numbers_of_philosophers);
	ptr->philosophe = malloc(sizeof(pthread_t) * ptr->numbers_of_philosophers);
	if (!ptr|| !ptr->mutex || !ptr->philosophe)
	{
		printf("ERROR\nMemory allocation failed\n");	
		exit(0);
	}
}

void	*action_philo(void *arg)
{
	t_philo *ptr;

	ptr = (t_philo *)arg;
	//eating
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

int	main(int argc, char **argv)
{
	t_philo			*ptr;

	ptr = NULL;
	if (argc != 6)
	{
		printf("ERROR\nMissing arguments/too much arguments\n");
		exit(0);
	}
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
