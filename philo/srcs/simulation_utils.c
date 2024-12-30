/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:12:46 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/30 09:09:09 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ph_sleep(long long time, t_table *table)
{
	long long	start;
	int			someone_died;

	start = get_current_time();
	while (get_current_time() - start <= time)
	{		
		pthread_mutex_lock(&table->write_mutex);
		someone_died = table->someone_died;
		pthread_mutex_unlock(&table->write_mutex);
		if (someone_died == 1)
			break ;
		usleep(100);
	}
}

int	check_dead(t_table *table)
{
	pthread_mutex_lock(&table->write_mutex);
	if (table->someone_died == 1)
		return (pthread_mutex_unlock(&table->write_mutex), 1);
	pthread_mutex_unlock(&table->write_mutex);
	return (0);
}

int is_ready(t_table *table)
{
	pthread_mutex_lock(&table->write_mutex);
	if (table->is_ready == table->nb_philos)
	{
		pthread_mutex_unlock(&table->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->write_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_mutex_lock(&table->write_mutex);
	table->is_ready++;
	pthread_mutex_unlock(&table->write_mutex);
	while (is_ready(table) == 0)
		usleep(100);
	if (philo->id % 2 == 0)
		ph_sleep(1, table);
	while (check_dead(table) == 0)
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}
