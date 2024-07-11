/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:01:09 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/10 21:57:58 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_forks(t_table *table)
{
	char	name_semaphore[32];
	char	base;
	int	i;

	base = 'a';
	name_semaphore[0] = '/';
	name_semaphore[1] = 'f';
	name_semaphore[2] = 'o';
	name_semaphore[3] = 'r';
	name_semaphore[4] = 'k';
	name_semaphore[5] = '_';
	table->forks = malloc(sizeof(sem_t *) * table->nb_philos);
	if (table->forks == NULL)
		return ;
	i = 0;
	while (i < table->nb_philos)
	{
		name_semaphore[6] = base;
		name_semaphore[7] = '\0';	
		table->forks[i] = sem_open(name_semaphore, O_CREAT | O_EXCL, 0644, 1);
		i++;
		base++;
	}
	table->log = sem_open("/semaphore_log", O_CREAT | O_EXCL, 0644, 1);
	if (table->log == SEM_FAILED)
		return ;
	table->waiter = sem_open("/waiter", O_CREAT | O_EXCL, 0644, table->nb_philos - 1);
	if (table->waiter == SEM_FAILED)
		return ;
}

static void	init_philo(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (table->philos == NULL)
		return ;
	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = get_current_time();
		i++;
	}
}

int	init_table(int argc, char **argv, t_table *table)
{
	table->nb_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->nb_meals = -1;
	if (argc == 6)
		table->nb_meals = ft_atol(argv[5]);
	table->philo_died = 0;
	table->start = get_current_time();
	init_philo(table);
	if (table->philos == NULL)
			exit(0);
	init_forks(table);
	return (1);
}
