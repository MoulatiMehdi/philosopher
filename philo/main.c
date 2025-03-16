/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:45:59 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 22:12:22 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*func(void *arg)
{
	t_philo	*philosopher;

	philosopher = arg;
	if (philosopher->id % 2 == 0)
		usleep(500);
	philosopher->last_meal = ft_timestamp();
	while (1)
	{
		pthread_mutex_lock(philosopher->lock_dead);
		if (*philosopher->stop)
		{
			pthread_mutex_unlock(philosopher->lock_dead);
			break ;
		}
		pthread_mutex_unlock(philosopher->lock_dead);
		ft_philo_eat(philosopher);
		ft_message(philosopher, "is sleeping");
		ft_msleep(philosopher->time_sleep);
		ft_message(philosopher, "is thinking");
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table		*table;
	pthread_t	observer;

	if (argc != 5 && argc != 6)
	{
		printf("./philo nbr_philos time_die time_eat time_sleep ");
		printf("[nbr_meals_per_philo]\n");
		return (0);
	}
	table = ft_table_new(argc, argv);
	ft_threads_create(&observer, table);
	ft_threads_wait(&observer, table);
	ft_table_destroy(&table);
	return (0);
}
