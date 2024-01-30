/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:03:41 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/29 15:46:40 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	m;
	int	stock;

	m = 0;
	i = 0;
	stock = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (str[i] == '-')
			m++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		stock = 10 * stock + (str[i] - 48);
		i++;
	}
	if (m == 1)
		return (-stock);
	else
		return (stock);
}
