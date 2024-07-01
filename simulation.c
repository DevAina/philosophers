/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:18:56 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/01 21:12:38 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    print_status(philo->table, philo->id, "is thinking");
}

void take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    print_status(philo->table, philo->id, "has taken a fork");
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    print_status(philo->table, philo->id, "has taken a fork");
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->died_mutex);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->table->died_mutex);

    print_status(philo->table, philo->id, "is eating");
    usleep(philo->table->time_to_eat * 1000);
    philo->meals_eaten++;
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void ft_sleep(t_philo *philo)
{
    print_status(philo->table, philo->id, "is sleeping");
    usleep(philo->table->time_to_sleep * 1000);
    //print_status(philo->table, philo->id, "is thinking");
}

void    *routine(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;

    if (philo->id % 2 == 0)
        usleep(1000);
    while (1)
    {
        /*if (check_death(table, philo))
        {
            break;
        }*/
        if (table->nb_meals != -1 && philo->meals_eaten >= table->nb_meals)
            break;

        think(philo); //TODO
        take_forks(philo);
        eat(philo);
        release_forks(philo);
        ft_sleep(philo);
        usleep(100000000);
    }
    return (NULL);
}