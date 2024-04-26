/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:53:13 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/26 13:53:32 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_vars(t_philo *data, char **argv)
{
    data->id = 0;
    data->one_philo_died = 0;
    data->nb_of_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->number_of_meal = -1;
    if (argv[5])
        data->number_of_meal = ft_atoi(argv[5]);
}

void	init_mutexes(t_philo *data)
{
    pthread_mutex_init(&data->print, NULL);
    pthread_mutex_init(&data->sleep, NULL);
    pthread_mutex_init(&data->check_death, NULL);
    pthread_mutex_init(&data->time_mutex, NULL);
    pthread_mutex_init(&data->philo_died, NULL);
    pthread_mutex_init(&data->eat_count_mutex, NULL);
}

void	allocate_memory(t_philo *data)
{
    data->last_meal_time = malloc(sizeof(long int) * data->nb_of_philosophers);
    data->last_meal = malloc(sizeof(int) * data->nb_of_philosophers);
    data->philo = malloc(sizeof(pthread_t) * data->nb_of_philosophers);
    data->philo_lock = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
    data->last_meal_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_of_philosophers);
    data->eat_count = malloc(sizeof(int) * data->nb_of_philosophers);
}

void	init_arrays(t_philo *data)
{
    int i = 0;
    while(i < data->nb_of_philosophers)
    {
        data->last_meal_time[i] = 0;
        data->eat_count[i] = 0;
        data->last_meal[i] = 0;
        i++;
    }
}

void	init_forks_and_locks(t_philo *data)
{
    int id = 0;
    while(id < data->nb_of_philosophers)
    {
        pthread_mutex_init(&data->forks[id], NULL);
        pthread_mutex_init(&data->philo_lock[id], NULL);
        pthread_mutex_init(&data->last_meal_mutex[id], NULL);
        id++;
    }
}