/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:16:23 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/09 15:20:54 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	think(t_philo *philo)
{
	print_status(philo->table, philo->id, "is thinking");
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
	usleep(philo->table->time_to_eat * 1000);
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
	usleep(philo->table->time_to_sleep * 1000);
}
