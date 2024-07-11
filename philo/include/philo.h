/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:16:10 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/09 15:19:48 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>
# include <limits.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_table		*table;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	long long	last_meal_time;
}	t_philo;

struct s_table
{
	t_philo			*philo;
	pthread_t		monitoring_death;
	int				nb_philos;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				nb_meals;
	long long		start;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	died_mutex;
};

/*********fc for utils************/
void		error(char *str);
int			all_argument_is_digit(int argc, char **argv);
long long	get_current_time(void);
void		print_status(t_table *table, int id, char *status);
int			check_death(t_table *table, t_philo *philo);
void		clean_up(t_table *table);
int			init_table(int argc, char **argv, t_table *table);
long		ft_atol(char *str);

/*********fc for thread death***************/
void		*monitoring_death(void *arg);

/**************fc for thread****************/
int			thread(t_table *table);

/********fc for simulation*********/
int			check_dead(t_table *table);
void		think(t_philo *philo);
void		*routine(void *arg);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		release_forks(t_philo *philo);
void		ft_sleep(t_philo *philo);

#endif
