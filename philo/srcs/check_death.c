/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:46:23 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/30 09:10:29 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	void	block_of_code(t_table *table)
{
	pthread_mutex_lock(&table->write_mutex);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->write_mutex);
}

static int	check_if_philo_died(t_table *table, int index)
{
	long long	current_time;
	long long	diff;

	current_time = get_current_time();
	pthread_mutex_lock(&table->died_mutex);
	diff = current_time - table->philo[index].last_meal_time;
	pthread_mutex_unlock(&table->died_mutex);
	if (diff >= table->time_to_die)
	{
		block_of_code(table);
		pthread_mutex_lock(&table->mutex_print);
		printf("%lld %d %s\n", current_time - table->start,
			table->philo->id, "died");
		pthread_mutex_unlock(&table->mutex_print);
		return (1);
	}
	return (0);
}

void	*monitoring_death(void *arg)
{
	t_table		*table;
	int			i;

	table = (t_table *)arg;
	while (is_ready(table) == 0)
		usleep(100);
	table->start = get_current_time();
	while (table->someone_died == 0)
	{
		usleep(10);
		i = 0;
		while (i < table->nb_philos)
		{
			if (check_if_philo_died(table, i))
				break ;
			i++;
		}
	}
	return (NULL);
}
