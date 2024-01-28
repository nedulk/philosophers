/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleden <kleden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:17:57 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/28 16:44:05 by kleden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_var(t_data *data, char **argv)
{
	int i;

	i = 0;
	///INITIALISATIONS DES ARGUMENTS
	data->numbers_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->number_of_meal = ft_atoi(argv[5]);
	pthread_mutex_init(&data->message, NULL);
	pthread_mutex_init(&data->lock, NULL);
	
	//ALLOCATIONS
	data->thread_id = malloc(sizeof(pthread_t) * data->nb_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numbers_of_philosophers);
	data->philosophe = malloc(sizeof(t_philo) * data->numbers_of_philosophers);
	if (!data->philosophe || !data->thread_id || !data->forks)
		return (0);

	//INITIALISATION ET ATTRIBUTION DES FOURCHETTES
	while(i < data->nb_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_of_philosophers)
	{
		data->philosophe[i].l_fork = &data->forks[i];
		data->philosophe[i].r_fork = &data->forks[i % (data->nb_of_philosophers - 1)];
		i++;
	}

	//INITIALISATION DES CONSTANTES POUR TOUS LES PHILOSOPHES
	i = 0;
	while (i < data->nb_of_philosophers)
	{
		data->philosophe[i].data = data; // ainsi chaque philosophe a acces aux informations le concernant
		data->philosophe[i].id = i;
		data->philosophe[i].eat_count = 0;
		data->philosophe[i].eating = 0;
		pthread_mutex_init(&data->philosophe[i].lock, NULL);
		i++
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 6 || argc < 5)
	{
		printf("ERROR\nMissing arguments/too much arguments\n");
		return (0);
	}
	init_var(&ptr, argv);
	data->start_time = get_time();
	init_thread(data);

	return (0);
}
