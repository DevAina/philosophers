/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:36:47 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/12 15:00:42 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think(t_philo *philo, t_table *table)
{
	print_status(table, philo->id, "is thinking");
}

void	take_fork(t_table *table, t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % table->nb_philos;
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
}

void	eat(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->mutex_meal);
	print_status(table, philo->id, "is eating");
	usleep(table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex_meal);
}

void	release_fork(t_table *table, t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % table->nb_philos;
	sem_post(table->forks[left_fork]);
	sem_post(table->forks[right_fork]);
}

void	ft_sleep(t_table *table, t_philo *philo)
{
	print_status(table, philo->id, "is sleeping");
	usleep(table->time_to_sleep * 1000);
}

void	routine(t_philo *philo, t_table *table)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		think(philo, table);
		if (table->nb_philos != 1)
		{
			take_fork(table, philo);
			eat(philo, table);
			release_fork(table, philo);
		}
		ft_sleep(table, philo);
	}
}
