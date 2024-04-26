/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:17:57 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/26 13:58:01 by kprigent         ###   ########.fr       */
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

	if (parsing(argc, argv) == 0)
		return (0);
	init_var(&data, argv);
	data.start_time = get_time();
	start_routine(&data);
	return (0);
}
