/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:18 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/21 21:43:12 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_threads_start(t_philo **philos, t_args *args)
{
	int	i;

	args->time_start = ft_timestamp();
	i = 0;
	while (i < args->size)
	{
		if (pthread_create(&(*philos)[i].thread, NULL, ft_thread_philo,
			&(*philos)[i]))
			return (0);
		i++;
	}
	if (pthread_create(&(args->monitor), NULL, ft_thread_monitor, philos))
		return (0);
	return (1);
}

int	ft_threads_wait(t_philo **philo, t_args *args)
{
	int	i;
	int	status;

	status = 1;
	i = 0;
	pthread_join(args->monitor, NULL);
	while (i < args->size)
	{
		if (pthread_join((*philo)[i].thread, NULL))
			status = 0;
		i++;
	}
	return (status);
}

int	ft_threads_stop(t_args *args)
{
	pthread_mutex_lock(&args->lock_death);
	args->is_dead = 1;
	pthread_mutex_unlock(&args->lock_death);
	return (1);
}
