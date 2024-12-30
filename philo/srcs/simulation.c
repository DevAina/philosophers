/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:16:23 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/30 09:05:43 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	think(t_philo *philo)
{
	long long	time_eat;
	long long	time_sleep;

	time_eat = philo->table->time_to_eat;
	time_sleep = philo->table->time_to_sleep;
	print_status(philo->table, philo->id, "is thinking");
	if (philo->table->nb_philos % 2)
	{
		ph_sleep((time_eat * 2) - time_sleep, philo->table);
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_status(philo->table, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_status(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo->table, philo->id, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->died_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->table->died_mutex);
	print_status(philo->table, philo->id, "is eating");
	ph_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->table->died_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->died_mutex);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	ft_sleep(t_philo *philo)
{
	print_status(philo->table, philo->id, "is sleeping");
	ph_sleep(philo->table->time_to_sleep, philo->table);
}
