/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:12:17 by trarijam          #+#    #+#             */
/*   Updated: 2024/07/12 15:11:15 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table table;
	int		status;
	//pthread_t monitor_death;

	if (argc == 5 || argc == 6)
	{
		if (!init_table(argc, argv, &table))
		{
			printf("Error init_table");
			return (1);
		}
		else
		{
			create_process(&table);
			/*if (pthread_create(&monitor_death, NULL, check_death, &table) != 0)
			{
				printf("Failed to create thread");
				clean_up(&table);
				return (1);
			}*/
			int i;
			while (1)
			{
				if (waitpid(-1, &status, 0) == -1)
					break;
				if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
				{
					i = 0;
					while (i < table.nb_philos)
					{
						kill(table.philos[i].pid, SIGKILL);
						i++;
					}
				}
				usleep(100);
			}
			i = 0;
			/*while (i < table.nb_philos)
			{
				waitpid(table.philos[i].pid, NULL, 0);
				i++;
			}*/
			//pthread_join(monitor_death, NULL);
			clean_up(&table);
		}
	}
	else
	{
		printf("Error input\n");
		return (1);
	}
	return (0);
}
