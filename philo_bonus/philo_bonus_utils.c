/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:04:31 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/12 15:11:39 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	ft_atol(char *str)
{
	int	sign;
	long	res;
	int	i;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	print_status(t_table *table, int id, char *state)
{
	long long	current_time;

	current_time = get_current_time() - table->start;
	sem_wait(table->log);
	if (table->philo_died != 1)
		printf("%llu %d %s\n", current_time, id, state);
	sem_post(table->log);
}

void	clean_up(t_table *table)
{
	char    name_semaphore[32];
	char    base;
	int i;

	i = 0;
	base = 'a';
	name_semaphore[0] = '/';
	name_semaphore[1] = 'f';
	name_semaphore[2] = 'o';
	name_semaphore[3] = 'r';
	name_semaphore[4] = 'k';
	name_semaphore[5] = '_';
	/*while (i < table->nb_philos)
	{
		waitpid(table->philos[i].pid, NULL, 0);
		i++;	    
	}*/
	i = 0;
	while (i < table->nb_philos)
	{
		name_semaphore[6] = base;
		name_semaphore[7] = '\0';
		sem_close(table->forks[i]);
		sem_unlink(name_semaphore);		
		base++;
		i++;
	}
	free(table->forks);
	sem_close(table->log);
	sem_unlink("/semaphore_log");
	sem_close(table->died);
	sem_unlink("/died");
	free(table->philos);
}
