/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:29:56 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/10 22:19:35 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (0);
		if (table->philos[i].pid == 0)
		{
			routine(&table->philos[i], table);
			exit(0);
		}	
		i++;
	}
	return (0);
}
