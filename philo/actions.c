/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:24:06 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/16 17:14:17 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

void	ft_message(t_philo *philosopher, char *str)
{
	pthread_mutex_lock(philosopher->lock_dead);
	if (*philosopher->stop == false)
		printf("%ld %ld %s\n", ft_timestamp() / 1000, philosopher->id, str);
	pthread_mutex_unlock(philosopher->lock_dead);
}

void	ft_philo_eat(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->fork_right);
	ft_message(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->fork_left);
	ft_message(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->meal_check);
	philosopher->iseating = true;
	ft_message(philosopher, "is eating");
	philosopher->last_meal = ft_timestamp();
	philosopher->eaten++;
	pthread_mutex_unlock(philosopher->meal_check);
	ft_msleep(philosopher->time_eat);
	philosopher->iseating = false;
	pthread_mutex_unlock(philosopher->fork_right);
	pthread_mutex_unlock(philosopher->fork_left);
}
