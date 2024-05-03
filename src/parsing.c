/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:21:46 by kprigent          #+#    #+#             */
/*   Updated: 2024/05/03 08:56:27 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fix_number(char *str)
{
	int		i;
	int		n;
	char	*tmp;

	n = 0;
	i = 0;
	tmp = ft_strdup(str);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf(RED "Error: Invalid character '%c' in argument\n" RESET,
				str[i]);
			if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
				&& str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
				str[i] = '\x1f';
			else
				n = 1;
		}
		i++;
	}
	if (n == 0)
		printf(YELLOW "Argument corrected : %s sould be %s\n" RESET, tmp, str);
	free(tmp);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	handle_big_number(char **argv, int i)
{
	long int	argument_value;

	argument_value = ft_atoi(argv[i]);
	if ((argument_value > 2147483647 || ft_strlen(argv[i]) > 10
			|| argument_value < 0) && i == 5)
	{
		printf(RED "Error: Argument %d is too big.\n" RESET, i);
		printf(YELLOW "You provided too much meal.\n" RESET);
		return (0);
	}
	return (1);
}

int	fix_and_check_length(char **argv, int i)
{
	long int	argument_value;

	argument_value = ft_atoi(argv[i]);
	if (argument_value < 0 && (ft_strlen(argv[i]) > 10))
	{
		printf(RED "Error: Argument %d is too big.\n" RESET, i);
		printf(YELLOW"Please choose a number between 0 and 2147483647.\n"RESET);
	}
	else if ((argument_value > 2147483647 || ft_strlen(argv[i]) > 10)
		&& i > 1 && i < 5)
	{
		printf(RED "Error: Argument %d is too big.\n" RESET, i);
		printf(YELLOW"You provided %ld ms,\napproximately %ld hours.\n",
			argument_value, argument_value / 3600000);
		printf(YELLOW"Please choose a number between 0 and 2147483647\n"RESET);
		return (0);
	}
	else if (i == 1 && ((argument_value > 200) || ft_strlen(argv[i]) > 3))
	{
		printf(RED "Error: Argument %d is too big.\n" RESET, i);
		printf(YELLOW "Please choose a number between 0 and 200\n" RESET);
		return (0);
	}
	return (1);
}

int	parsing(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc > 6)
	{
		printf(RED "Error: Too much arguments\n" RESET);
		return (0);
	}
	if (argc < 5)
	{
		printf(RED "Error: Not enough arguments\n" RESET);
		return (0);
	}
	while (argv[++i])
	{
		if (is_number(argv[i]) == 0)
		{
			fix_number(argv[i]);
			return (0);
		}
		if (handle_big_number(argv, i) == 0
			|| fix_and_check_length(argv, i) == 0)
			return (0);
	}
	return (1);
}
