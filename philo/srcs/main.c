/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:15:44 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/30 08:09:47 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
		if (!all_argument_is_digit(argc, argv)
			|| !init_table(argc, argv, &table))
			return (1);
	else
	{
		if (!thread(&table))
			return (1);
	}
	else
	{
		write(2, "Error: wrong number of arguments\n", 34);
		write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat"
			" time_to_sleep [number_of_meals]\n", 95);
		return (1);
	}
	clean_up(&table);
	return (0);
}
