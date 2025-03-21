/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:08 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/19 00:17:43 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread_monitor(void *arg)
{
	t_philo	*philo;
	t_args	*args;
	long	time_curr;
	long	last_meal;

	philo = arg;
	args = philo->args;
	while (1)
	{
		time_curr = ft_timestamp() - args->time_start;
		sem_wait(philo->lock_meal);
		last_meal = time_curr - philo->meal_last;
		sem_post(philo->lock_meal);
		if (last_meal > args->time_die)
		{
			sem_wait(args->lock_write);
			printf("%013ld %d died\n", time_curr, philo->id + 1);
			sem_post(args->lock_death);
		}
		ft_msleep(1);
	}
	return (NULL);
}

void	*ft_thread_philos_kill(void *arg)
{
	t_philo	*philos;
	t_args	*args;

	philos = arg;
	args = philos[0].args;
	sem_wait(args->lock_death);
	ft_process_stop(philos, args);
	return (NULL);
}
