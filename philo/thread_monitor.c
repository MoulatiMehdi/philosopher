/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:08 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/21 21:36:42 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

int	ft_monitor_philo(t_philo *philo, long time_curr)
{
	int		is_dead;
	long	last_meal;
	t_args	*args;

	is_dead = 0;
	args = philo->args;
	pthread_mutex_lock(&philo->lock_meal);
	last_meal = time_curr - philo->meal_last;
	pthread_mutex_unlock(&philo->lock_meal);
	if (last_meal > args->time_die)
	{
		pthread_mutex_lock(&args->lock_write);
		pthread_mutex_lock(&args->lock_death);
		args->is_dead = 1;
		pthread_mutex_unlock(&args->lock_death);
		printf("%013ld %d died\n", time_curr, philo->id + 1);
		pthread_mutex_unlock(&args->lock_write);
		is_dead = 1;
	}
	return (is_dead);
}

int	ft_thread_ismeal(t_philo *philo, t_args *args)
{
	int	is_meal_max;

	pthread_mutex_lock(&philo->lock_counter);
	is_meal_max = (philo->meal_count >= args->meal_min && args->meal_min > -1);
	pthread_mutex_unlock(&philo->lock_counter);
	return (is_meal_max);
}

void	*ft_thread_monitor(void *arg)
{
	t_philo	**philos;
	t_args	*args;
	long	time_curr;
	int		i;
	int		c;

	philos = arg;
	args = philos[0]->args;
	while (1)
	{
		i = 0;
		c = 0;
		time_curr = ft_timestamp() - args->time_start;
		while (i < args->size)
		{
			if (ft_monitor_philo(&(*philos)[i], time_curr))
				return (NULL);
			c += ft_thread_ismeal(&(*philos)[i], args);
			i++;
		}
		if (c >= args->size)
			break ;
	}
	return (NULL);
}
