/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:36:47 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/10 22:13:23 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo, t_table *table)
{
	int	left_fork;
	int	right_fork;

	if (philo->id % 2 == 0)
		usleep(1000);
	left_fork = philo->id - 1;
	right_fork = philo->id % table->nb_philos;
	while (table->philo_died == 0)
	{
		//think
		print_status(table, philo->id, "is thinking");
		//
		
		//take fork
		if (philo->id % 2)
		{
			sem_wait(table->forks[right_fork]);
			print_status(table, philo->id, "has taken a fork");
			sem_wait(table->forks[left_fork]);
			print_status(table, philo->id, "has taken a fork");
		}
		else
		{
			sem_wait(table->forks[left_fork]);
			print_status(table, philo->id, "has taken a fork");
			sem_wait(table->forks[right_fork]);
			print_status(table, philo->id, "has taken a fork");
		}
		
		//eat
		print_status(table, philo->id, "is eating");
		philo->last_meal_time = get_current_time();
		usleep(table->time_to_eat * 1000);
		philo->meals_eaten++;

		//release_forks
		sem_post(table->forks[left_fork]);
		sem_post(table->forks[right_fork]);
		

		//sleep
		print_status(table, philo->id, "is sleeping");
		usleep(table->time_to_sleep * 1000);
	}
}
