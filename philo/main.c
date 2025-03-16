/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:45:59 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/16 23:16:55 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*func(void *arg)
{
	t_philo	*philosopher;

	philosopher = arg;
	pthread_mutex_lock(philosopher->lock_dead);
	if (*philosopher->stop)
	{
		pthread_mutex_unlock(philosopher->lock_dead);
		return (NULL);
	}
	pthread_mutex_unlock(philosopher->lock_dead);
	if (philosopher->id % 2 == 0)
		usleep(500);
	philosopher->last_meal = ft_timestamp();
	while (1)
	{
		pthread_mutex_lock(philosopher->lock_dead);
		if (*philosopher->stop)
			break ;
		pthread_mutex_unlock(philosopher->lock_dead);
		ft_philo_eat(philosopher);
		ft_message(philosopher, "is sleeping");
		ft_msleep(philosopher->time_sleep);
		ft_message(philosopher, "is thinking");
	}
	pthread_mutex_unlock(philosopher->lock_dead);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table		*table;
	pthread_t	observer;

	if (!ft_args_isvalid(argc, argv))
		return (1);
	table = ft_table_new(argc, argv);
	if (table == NULL)
	{
		printf("Error : Table allocation Failed\n");
		return (1);
	}
	if (ft_threads_create(&observer, table) == 0)
		ft_threads_wait(&observer, table);
	else
		printf("Error : Thread allocation Failed\n");
	ft_table_destroy(&table);
	return (0);
}
