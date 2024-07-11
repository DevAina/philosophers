/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:12:46 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/09 15:33:59 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_dead(t_table *table)
{
	pthread_mutex_lock(&table->write_mutex);
	if (table->someone_died == 1)
		return (pthread_mutex_unlock(&table->write_mutex), 1);
	pthread_mutex_unlock(&table->write_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (check_dead(table) == 0)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
