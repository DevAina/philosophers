/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:26:22 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/30 08:45:42 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	void	init_last_meal_time(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->nb_philos)
	{
		philo[i].last_meal_time = philo->table->start;
		i++;
	}
}

static	int	return_and_clear(t_table *table, char *display_error)
{
	error(display_error);
	clean_up(table);
	return (0);
}

int	thread(t_table *table)
{
	int	i;

	table->start = get_current_time();
	init_last_meal_time(table->philo);
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
	return (1);
}
