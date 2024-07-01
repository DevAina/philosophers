/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:43:08 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/01 21:01:59 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    print_status(t_table *table, int id, char *status)
{
    long now;

    now = get_current_time() - table->start;
    pthread_mutex_lock(&table->write_mutex);
    if (!table->someone_died)
    {
        printf("%ld %d %s\n", now, id, status);
        pthread_mutex_unlock(&table->write_mutex);
    }
    pthread_mutex_unlock(&table->write_mutex);
}

int check_death(t_table *table, t_philo *philo)
{
    pthread_mutex_lock(&table->died_mutex);
    if (table->someone_died)
    {
        pthread_mutex_unlock(&table->died_mutex);
        return (1);
    }
    if (get_current_time() - philo->last_meal_time > table->time_to_die)
    {
        printf("Philo %d died. Current time: %ld, Last meal: %d, Diff: %ld, Time to die: %d\n", 
           philo->id, get_current_time(), philo->last_meal_time, 
           get_current_time() - philo->last_meal_time, table->time_to_die);
        table->someone_died = 1;
        pthread_mutex_unlock(&table->died_mutex);
        return (1);
    }
    pthread_mutex_unlock(&table->died_mutex);
    return (0);
}

long    ft_atol(char *str)
{
    long res;
    int sign;
    int i;

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

void    clean_up(t_table *table)
{
    int i;

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