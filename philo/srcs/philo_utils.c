/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:16:00 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/09 15:31:07 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(2, RED, 5);
		write (2, &str[i], 1);
		write(2, RESET, 4);
		i++;
	}
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_table *table, int id, char *status)
{
	long long	now;

	now = get_current_time() - table->start;
	pthread_mutex_lock(&table->write_mutex);
	if (!table->someone_died)
		printf("%lld %d %s\n", now, id, status);
	pthread_mutex_unlock(&table->write_mutex);
}

long	ft_atol(char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	if (table->forks)
	{
		while (i < table->nb_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	if (table->philo)
		free(table->philo);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->died_mutex);
}
