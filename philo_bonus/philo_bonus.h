/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:19:08 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/10 21:49:28 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo
{
	int			id;
	pid_t			pid;
	int			meals_eaten;
	unsigned long long	last_meal_time;
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	int	philo_died;
	int	nb_meals;
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	unsigned long long	start;
	sem_t	**forks;
	sem_t	*waiter;
	sem_t	*log;
}	t_table;

unsigned long long	get_current_time(void);
void	print_status(t_table *table, int id, char *state);
long	ft_atol(char *str);
int	init_table(int argc, char **argv, t_table *table);
void	clean_up(t_table *table);

int	create_process(t_table *table);

void	routine(t_philo *philo, t_table *table);

void	*check_death(void *arg);
#endif
