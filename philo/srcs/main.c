/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:15:44 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/09 13:29:42 by trarijam         ###   ########.fr       */
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
		error("correct is: ./philosopher 9 500 200 100 [5]\n");
		return (1);
	}
	return (0);
}
