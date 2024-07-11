/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:26:22 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/09 15:32:09 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	int	return_and_clear(t_table *table, char *display_error)
{
	error(display_error);
	clean_up(table);
	return (0);
}

int	thread(t_table *table)
{
	int	i;

	if (pthread_create(&table->monitoring_death,
			NULL, monitoring_death, table) != 0)
		return (return_and_clear(table, "Error create thread\n"));
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philo[i].thread,
				NULL, routine, &table->philo[i]) != 0)
			return (return_and_clear(table, "Error create thread\n"));
		i++;
	}
	if (pthread_join(table->monitoring_death, NULL) != 0)
		return (return_and_clear(table, "Error to join thread\n"));
	i = 0;
	while (i < table->nb_philos)
	{
		if ((pthread_join(table->philo[i].thread, NULL)) != 0)
			return (return_and_clear(table, "Error to join thread\n"));
		i++;
	}
	clean_up(table);
	return (1);
}
