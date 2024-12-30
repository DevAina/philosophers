/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:15:24 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/30 08:58:53 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	void	init_forks(t_table *table)
{
	int	nb_forks;
	int	i;

	i = 0;
	nb_forks = table->nb_philos;
	table->state_forks = malloc(sizeof(int) * nb_forks);
	table->forks = malloc(sizeof(pthread_mutex_t) * (nb_forks));
	if (table->forks == NULL || table->state_forks == NULL)
	{
		error("Error malloc forks");
		return ;
	}
	while (i < nb_forks)
	{
		table->state_forks[i] = 0;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->mutex_print, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->died_mutex, NULL);
}

static void	init_philo(t_table *table)
{
	int	nb_philos;
	int	i;

	i = 0;
	nb_philos = table->nb_philos;
	table->philo = malloc(sizeof(t_philo) * (nb_philos));
	if (table->philo == NULL)
	{
		error("Error malloc philo\n");
		return ;
	}
	while (i < nb_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].is_full = 0;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % nb_philos;
		table->philo[i].meals_eaten = 0;
		table->philo[i].table = table;
		i++;
	}
}

int	init_table(int argc, char **argv, t_table *table)
{
	table->nb_philos = ft_atol(argv[1]);
	if (table->nb_philos <= 0)
	{
		error("Error: the number of philosophers cannot be 0 or negative\n");
		return (0);
	}
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->nb_meals = -1;
	if (argc == 6)
	{
		table->nb_meals = ft_atol(argv[5]);
		if (table->nb_meals <= 0)
		{
			error("Error: nb_meals cannot be 0 or negative\n");
			return (0);
		}
	}
	table->is_ready = 0;
	table->someone_died = 0;
	table->end_simulation = 0;
	init_philo(table);
	init_forks(table);
	return (1);
}
