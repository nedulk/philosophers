/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:17:57 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/25 20:08:37 by kprigent         ###   ########.fr       */
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
	data->one_philo_died = 0;
	///INITIALISATIONS DES ARGUMENTS
	data->nb_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_meal = -1;
	if (argv[5])
		data->number_of_meal = ft_atoi(argv[5]);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->sleep, NULL);
	pthread_mutex_init(&data->check_death, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->philo_died, NULL);
	pthread_mutex_init(&data->eat_count_mutex, NULL);
	
	//ALLOCATIONS
	data->last_meal_time = malloc(sizeof(long int) * data->nb_of_philosophers);
	data->last_meal = malloc(sizeof(int) * data->nb_of_philosophers);
	data->philo = malloc(sizeof(pthread_t) * data->nb_of_philosophers);
	data->philo_lock = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
	data->last_meal_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
	data->eat_count = malloc(sizeof(int) * data->nb_of_philosophers);
	if (!data->philo || !data->philo_lock || !data->forks
		|| !data->eat_count)
		return ;

	//INITIALISATION
	i = 0;
	while(data->last_meal_time[i])
	{
		data->last_meal_time[i] = 0;
		i++;
	}
	i = 0;
	while(data->eat_count[i])
	{
		data->eat_count[i] = 0;
		i++;
	}
	i = 0;
	while(data->last_meal[i])
	{
		data->last_meal[i] = 0;
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
	id = 0;
	while (id < data->nb_of_philosophers)
	{
		pthread_mutex_init(&data->last_meal_mutex[id], NULL);
		id++;
	}
}

int every_philo_ate(t_philo *data, int id)
{
	pthread_mutex_lock(&data->eat_count_mutex);
	if (data->eat_count[id] > data->number_of_meal)
	{
		pthread_mutex_unlock(&data->eat_count_mutex);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->eat_count_mutex);
	return (0);
}
void *death_check_routine(void* arg)
{
	t_philo *data = (t_philo *)arg;
	int id;

	id = 0;
	while (1)
	{
		if (check_death_philo(data, id) == 1)
		{
			return (NULL);
		}
		id = (id + 1) % data->nb_of_philosophers;
	}
	return (NULL);
}

void *eat_count_check_routine(void* arg)
{
	t_philo *data = (t_philo *)arg;
	int id;

	id = 0;
	while (1)
	{
		pthread_mutex_lock(&data->philo_died);
		if (data->one_philo_died == 1)
		{
			pthread_mutex_unlock(&data->philo_died);
			return (NULL);
		}
		else
			pthread_mutex_unlock(&data->philo_died);
		if (data->number_of_meal != -1 && every_philo_ate(data, id) == 1)
		{
			printf(GREEN "Everyone ate enough\n" RESET);
			exit(0);
		}
		id = (id + 1) % data->nb_of_philosophers;
	}
	return (NULL);
}

void *philo_routine(void* arg)
{
	t_philo_data *philo_data = (t_philo_data *)arg;
	t_philo *data = philo_data->data;
	int id = philo_data->id;

	while (1)
	{
		if (id % 2 == 0)
			usleep(100);
		pthread_mutex_lock(&data->philo_died);
		if (data->one_philo_died == 1)
		{
			pthread_mutex_unlock(&data->philo_died);	
			return (NULL);
		}
		pthread_mutex_unlock(&data->philo_died);
		start_dinner(data, id);
	}
	return (NULL);
}

void ft_join(t_philo *data, pthread_t death_check_thread, pthread_t eat_count_check_thread)
{
	int id = 0;
	void *return_value;
	
	while (id < data->nb_of_philosophers)
	{
		pthread_join(data->philo[id], &return_value);
		id++;
	}
	if (data->number_of_meal != -1)
		pthread_join(eat_count_check_thread, &return_value);
	pthread_join(death_check_thread, &return_value);
}

void	start_routine(t_philo *data)
{
	int id;
	t_philo_data philo_data[data->nb_of_philosophers];
	pthread_t death_check_thread = 0;
	pthread_t eat_count_check_thread = 0;
		
	id  = 0;
	while (id < data->nb_of_philosophers)
	{
		philo_data[id].data = data;
		philo_data[id].id = id;
		pthread_create(&(data->philo[id]), NULL, philo_routine, (void*)&philo_data[id]);
		id++;
	}
	pthread_create(&death_check_thread, NULL, death_check_routine, (void*)data);
	if (data->number_of_meal != -1)
		pthread_create(&eat_count_check_thread, NULL, eat_count_check_routine, (void*)data);
	ft_join(data, death_check_thread, eat_count_check_thread);
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
