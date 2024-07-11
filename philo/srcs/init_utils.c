/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:43:08 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/09 14:04:49 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	argument_is_digit(char *argv)
{
	int	i;

	i = 0;
	while ((argv[i] >= 9 && argv[i] <= 13) || argv[i] == ' ')
	{
		i++;
	}
	if (argv[i] == '-')
		i++;
	while (argv[i] != '\0')
	{
		if (argv[i] >= '0' && argv[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	all_argument_is_digit(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!argument_is_digit(argv[i]))
		{
			error("Error: argument is not digit\n");
			return (0);
		}
		if (i != 1 && ft_atol(argv[i]) > INT_MAX)
		{
			error("Error: argument is not int. The limit is .\n");
			return (0);
		}
		else if (i == 1 && ft_atol(argv[i]) >= 7889)
		{
			error("Error: limit of number of philo is error 7888.\n");
			return (0);
		}
		i++;
	}
	return (1);
}
