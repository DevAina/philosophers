/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:32:37 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/01 19:59:53 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philo
{
    int         id;
    pthread_t   thread;
    t_table     *table;
    int         left_fork;
    int         right_fork;
    int         meals_eaten;
    int         last_meal_time;
} t_philo;

struct s_table
{
    t_philo *philo;
    int     nb_philos;
    int     time_to_die;
    int     time_to_sleep;
    int     time_to_eat;
    int     nb_meals;
    long    start;
    int     someone_died;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    pthread_mutex_t died_mutex;
};

/*******utils******/
long    get_current_time(void);
void    print_status(t_table *table, int id, char *status);
int     check_death(t_table *table, t_philo *philo);
void    clean_up(t_table *table);
int    init_table(int argc, char **argv, t_table *table);
long    ft_atol(char *str);
void    *routine(void *arg);

#endif