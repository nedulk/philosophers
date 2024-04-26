/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:03:41 by kprigent          #+#    #+#             */
/*   Updated: 2024/04/26 14:56:10 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_len(const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*target;
	int		i;

	target = malloc(sizeof(char) * (ft_len(src) + 1));
	if (target == NULL)
		return (NULL);
	i = 0;
	while (i < ft_len(src))
	{
		target[i] = src[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}

long int	ft_atoi(const char *str)
{
	int			i;
	int			m;
	long int	stock;

	i = 0;
	stock = 0;
	m = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		stock = stock * 10 + (str[i] - 48);
		i++;
	}
	if (m == 1)
		return (-stock);
	else
		return (stock);
}
