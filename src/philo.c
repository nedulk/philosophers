/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:17:57 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/30 18:09:53 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_var(t_philo *data, char **argv)
{
	int id;
	int	i;

	i = 0;
	id = 0;
	data->id = 0;
	data->eat_count = 0;
	///INITIALISATIONS DES ARGUMENTS
	data->nb_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->number_of_meal = ft_atoi(argv[5]);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->sleep, NULL);
	
	//ALLOCATIONS
	data->philo = malloc(sizeof(pthread_t) * data->nb_of_philosophers);
	data->philo_lock = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
	data->eat_count = malloc(sizeof(int) * data->nb_of_philosophers);
	if (!data->philo || !data->philo_lock || !data->forks || !data->eat_count)
		return ;

	//INITIALISATION
	while(data->eat_count[i])
	{
		data->eat_count[i] = 0;
		i++;
	}
	//INITIALISATION DES FOURCHETTES
	while(id < data->nb_of_philosophers)
	{
		pthread_mutex_init(&data->forks[id], NULL);
		id++;
	}
	id = 0;
	//INITIALISATION DES LOCKS POUR TOUS LES PHILOSOPHES
	while (id < data->nb_of_philosophers)
	{
		pthread_mutex_init(&data->philo_lock[id], NULL);
		id++;
	}
}

int every_philo_ate(t_philo *data)
{
	int	i;

	i = 0;
	while (data->eat_count[i] >= data->number_of_meal)
	{
		if (i == data->nb_of_philosophers - 1)
		{
			printf("0 : %d\n", data->eat_count[0]);
			printf("1 : %d\n", data->eat_count[1]);
			printf("2 : %d\n", data->eat_count[2]);
			printf("3 : %d\n", data->eat_count[3]);
			printf("4 : %d\n", data->eat_count[4]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	start_routine(t_philo *data)
{
	int id;

	while (every_philo_ate(data) == 0)
	{
		id  = 0;
		while (id < data->nb_of_philosophers)
		{
			pthread_create(&(data->philo[id]), NULL, eat, (void*)data);
			id++;
		}
		id = 0;
		while (id < data->nb_of_philosophers)
		{
			pthread_join(data->philo[id], NULL);
			id++;
		}
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	t_philo	data;

	if (argc > 6 || argc < 5)
	{
		printf("ERROR\nMissing arguments/too much arguments\n");
		return (0);
	}
	init_var(&data, argv);
	data.start_time = get_time();
	start_routine(&data);
	return (0);
}
