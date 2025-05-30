/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:06 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/19 13:36:50 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	ft_philo_init(t_philo *philo, t_fork *forks[PHILO_MAX], t_args *args)
{
	philo->args = args;
	philo->meal_last = 0;
	philo->meal_count = 0;
	if (philo->id % 2 == 0)
	{
		philo->fork_right = &(*forks)[philo->id];
		philo->fork_left = &(*forks)[(philo->id + 1) % args->size];
	}
	else
	{
		philo->fork_right = &(*forks)[(philo->id + 1) % args->size];
		philo->fork_left = &(*forks)[philo->id];
	}
	pthread_mutex_init(&philo->lock_meal, NULL);
	pthread_mutex_init(philo->fork_right, NULL);
}

int	ft_philos_init(t_philo philos[300], t_fork forks[PHILO_MAX], t_args *args)
{
	int	id;

	id = 0;
	while (id < args->size)
	{
		philos[id].id = id;
		ft_philo_init(&philos[id], &forks, args);
		id++;
	}
	return (1);
}

void	ft_free_memory(t_philo *philos, t_fork *forks)
{
	free(philos);
	free(forks);
}
