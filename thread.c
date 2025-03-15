/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:39:22 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 22:09:12 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_threads_detach(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->size)
	{
		pthread_detach(table->philosophers[i]->thread);
		i++;
	}
}

void	ft_threads_join(pthread_t *observer, t_table *table)
{
	size_t	i;

	pthread_join(*observer, NULL);
	i = 0;
	while (i < table->size)
	{
		pthread_join(table->philosophers[i]->thread, NULL);
		i++;
	}
}

void	ft_threads_create(pthread_t *observer, t_table *table)
{
	t_philo	*philosopher;
	size_t	i;

	i = 0;
	pthread_create(observer, NULL, ft_observer_should_stop, table);
	while (i < table->size)
	{
		philosopher = table->philosophers[i];
		pthread_create(&philosopher->thread, NULL, func, philosopher);
		i++;
	}
}
