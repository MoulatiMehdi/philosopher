/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:24:06 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 21:27:37 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

void	ft_message(t_philo *philosopher, char *str)
{
	pthread_mutex_lock(philosopher->lock_dead);
	if (*philosopher->stop == false)
		printf("%ld %ld %s\n", ft_timestamp(), philosopher->id, str);
	pthread_mutex_unlock(philosopher->lock_dead);
}

void	ft_philo_eat(t_philo *philosopher)
{
	ft_forks_take(philosopher);
	pthread_mutex_lock(philosopher->meal_check);
	philosopher->last_meal = ft_timestamp();
	ft_message(philosopher, "is eating");
	philosopher->state = EATING;
	philosopher->eaten++;
	pthread_mutex_unlock(philosopher->meal_check);
	ft_msleep(philosopher->time_eat);
	pthread_mutex_lock(philosopher->meal_check);
	philosopher->last_meal = ft_timestamp();
	pthread_mutex_unlock(philosopher->meal_check);
	ft_forks_put(philosopher);
}

void	ft_philo_sleep(t_philo *philosopher)
{
	philosopher->state = SLEEPING;
	ft_message(philosopher, "is sleeping");
	ft_msleep(philosopher->time_sleep);
}

void	ft_philo_think(t_philo *philosopher)
{
	philosopher->state = THINKING;
	ft_message(philosopher, "is thinking");
}

void	ft_philo_die(t_philo *philosopher)
{
	philosopher->state = DYING;
	ft_message(philosopher, "\033[1;91mis dead\033[0m");
}
