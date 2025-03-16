/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:39:22 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/16 23:07:55 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

void	ft_threads_wait(pthread_t *observer, t_table *table)
{
	size_t	i;

	i = 0;
	pthread_join(*observer, NULL);
	while (i < table->size)
	{
		pthread_detach(table->philosophers[i]->thread);
		i++;
	}
}

int	ft_threads_create(pthread_t *observer, t_table *table)
{
	t_philo	*philosopher;
	size_t	i;

	i = 0;
	pthread_mutex_lock(table->lock_dead);
	if (pthread_create(observer, NULL, ft_observer_should_stop, table) != 0)
	{
		table->stop = true;
		pthread_mutex_unlock(table->lock_dead);
		return (1);
	}
	while (i < table->size)
	{
		philosopher = table->philosophers[i];
		if (pthread_create(&philosopher->thread, NULL, func, philosopher) != 0)
		{
			pthread_detach(*observer);
			while (i > 0)
			{
				i--;
				pthread_detach(philosopher->thread);
			}
			table->stop = true;
			pthread_mutex_unlock(table->lock_dead);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(table->lock_dead);
	return (0);
}
