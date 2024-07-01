/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:46:10 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/01 21:04:30 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>

int main(int argc, char **argv)
{
    t_table table;
    int     i;

    if (argc == 5 || argc == 6)
        if (!init_table(argc, argv, &table))
        {
            printf("Error to init data");
            exit(EXIT_FAILURE);
        }
        else
        {
            i = 0;
            while (i < table.nb_philos)
            {
                int result = pthread_create(&table.philo[i].thread, NULL, routine, &table.philo[i]);
		        if (result != 0)
                {
                    //printf("Error to create thread\n %s", strerror(result));
                    
			        errno = result;
			        perror("Error creating thread");
			        clean_up(&table);
                    exit(EXIT_FAILURE);
                }
                i++;
            }
            i = 0;
            while (i < table.nb_philos)
            {
                if ((pthread_join(table.philo[i].thread, NULL)) != 0)
                {
                    printf("Error to join thread\n");
                    clean_up(&table);
                    exit(EXIT_FAILURE);
                }
                i++;
            }
            
        }
    else
    {
        printf("correct is: ./philosopher 9 500 200 [5]\n");
        return (1);
    }
    return (0);
}
