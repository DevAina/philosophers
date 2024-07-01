/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:51:20 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/01 21:04:27 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void     init_forks(t_table *table)
{
    int nb_forks;
    int i;

    i = 0;
    nb_forks = table->nb_philos;
    table->forks = malloc(sizeof(pthread_mutex_t) * (nb_forks));
    if (table->forks == NULL)
    {
        printf("Error malloc forks");
        exit(EXIT_FAILURE);
    }
    while (i <  nb_forks)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&table->write_mutex, NULL);
    pthread_mutex_init(&table->died_mutex, NULL);
}

static void    init_philo(t_table *table)
{
    int nb_philos;
    int i;

    i = 0;
    nb_philos = table->nb_philos;
    table->philo = malloc(sizeof(t_philo) * (nb_philos));
    if (table->philo == NULL)
    {
        printf("Error malloc philos");
        exit(EXIT_FAILURE);
    }
    while (i <  nb_philos)
    {
        table->philo[i].id = i + 1;
        table->philo[i].left_fork = i;
        table->philo[i].right_fork = (i + 1) % nb_philos;
        table->philo[i].meals_eaten = 0;
        table->philo[i].last_meal_time = table->start;
        table->philo[i].table = table;
        i++;
    }
}

int   init_table(int argc, char **argv, t_table *table)
{
    table->nb_philos = ft_atol(argv[1]);
    if (table->nb_philos <= 0)
    {
        printf("Error: le nombre de philosophe ne peut pas être 0 ou négatif\n");
        exit(EXIT_FAILURE);
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
            printf("Error: le nombre de nb_meals ne peut pas être 0 ou négatif\n");
            exit(EXIT_FAILURE);
        }
    }
    table->someone_died = 0;
    table->start = get_current_time();
    init_philo(table);
    init_forks(table);
    return (1);
}
