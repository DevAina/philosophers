/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:58:24 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/11 08:16:02 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		kill(table->philos[i].pid, SIGKILL);
		i++;
	}
}

void	*check_death(void *arg)
{
	unsigned long long	current_time;
	unsigned long long	diff;
	int	i;
	t_table	*table;

	table = (t_table *)arg;
	while (table->philo_died == 0)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			current_time = get_current_time();
			diff = current_time - table->philos[i].last_meal_time;
			if (((int)diff > table->time_to_die) || (table->nb_meals != -1 && table->philos[i].meals_eaten > table->nb_meals))
			{
				table->philo_died = 1;
				printf("%llu %d %s\n", current_time - table->start, table->philos[i].id, "died");
				kill_philo(table);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
