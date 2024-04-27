/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:17:57 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/27 13:12:15 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_var(t_philo *data, char **argv)
{
	init_vars(data, argv);
	init_mutexes(data);
	allocate_memory(data);
	if (!data->philo || !data->philo_lock || !data->forks || !data->eat_count)
		return ;
	init_arrays(data);
	init_forks_and_locks(data);
}

void	start_routine(t_philo *data)
{
	int				id;
	t_philo_data	*philo_data;
	pthread_t		death_check_thread;
	pthread_t		eat_count_check_thread;

	death_check_thread = 0;
	eat_count_check_thread = 0;
	id = 0;
	philo_data = malloc(sizeof(t_philo_data) * data->nb_of_philosophers);
	while (id < data->nb_of_philosophers)
	{
		philo_data[id].data = data;
		philo_data[id].id = id;
		pthread_create(&(data->philo[id]), NULL,
			philo_routine, (void*)&philo_data[id]);
		id++;
	}
	usleep(100);
	pthread_create(&death_check_thread, NULL, death_check_routine,
		(void*)data);
	if (data->number_of_meal != -1)
		pthread_create(&eat_count_check_thread, NULL, eat_count_check_routine,
			(void*)data);
	ft_join(data, death_check_thread, eat_count_check_thread);
	free(philo_data);
}

int	main(int argc, char **argv)
{
	t_philo	data;

	if (parsing(argc, argv) == 0)
		return (0);
	init_var(&data, argv);
	if (data.nb_of_philosophers == 1)
		printf("0 1 has taken a fork\n");
	data.start_time = get_time();
	start_routine(&data);
	free_memory(&data);
	return (0);
}
