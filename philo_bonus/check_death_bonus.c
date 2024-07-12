/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:58:24 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/12 15:10:17 by trarijam         ###   ########.fr       */
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

/*void	*check_death(void *arg)
{
	long long	current_time;
	long long	diff;
	int	i;
	t_table	*table;

	table = (t_table *)arg;
	while (table->philo_died == 0)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			sem_wait(table->died);
			current_time = get_current_time();
			diff = current_time - table->philos[i].last_meal_time;
			if ((diff > (long long)table->time_to_die) || (table->nb_meals != -1 && table->philos[i].meals_eaten > table->nb_meals))
			{
				sem_wait(table->log);
				table->philo_died = 1;
				sem_post(table->log);
				printf("%llu %d %s\n", current_time - table->start, table->philos[i].id, "died");
				sem_post(table->died);
				kill_philo(table);
				break ;
			}
			sem_post(table->died);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}*/

void	*check_death(void *arg)
{
	t_philo		*philo;
	long long current_time;
	long long		diff;

	philo = (t_philo *)arg;
	while (1)
	{
		current_time = get_current_time();
		sem_wait(philo->table->died);
		pthread_mutex_lock(&philo->mutex_meal);
		diff = current_time - philo->last_meal_time;
		pthread_mutex_unlock(&philo->mutex_meal);
		if ((diff > philo->table->time_to_die) || (philo->table->nb_meals != -1
			&& philo->meals_eaten > philo->table->nb_meals))
		{
			/*sem_wait(philo->table->log);
			philo->table->philo_died = 1;
			sem_post(philo->table->log);*/
			sem_wait(philo->table->log);
			printf("%llu %d %s\n", current_time - philo->table->start, philo->id, "died");
			sem_post(philo->table->died);
			clean_up(philo->table);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->table->died);
		usleep(100);
	}
	return (NULL);
}

