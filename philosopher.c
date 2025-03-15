/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:46:06 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 20:54:51 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*ft_philosopher_new(void)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(t_philo));
	if (philosopher == NULL)
		return (NULL);
	philosopher->last_meal = 0;
	philosopher->fork_left = NULL;
	philosopher->fork_right = NULL;
	philosopher->meal_check = NULL;
	philosopher->lock_dead = NULL;
	philosopher->eaten = 0;
	philosopher->time_die = 0;
	philosopher->time_eat = 0;
	philosopher->time_sleep = 0;
	philosopher->min_eat = 0;
	return (philosopher);
}

void	ft_philosopher_destroy(t_philo **philosopher)
{
	free(*philosopher);
	*philosopher = NULL;
}

bool	ft_philo_isdead(t_philo *philo)
{
	bool	ans;

	pthread_mutex_lock(philo->meal_check);
	if (philo->last_meal == 0)
		ans = false;
	else
	{
		ans = (ft_timestamp() - philo->last_meal > philo->time_die)
			&& philo->state != EATING;
	}
	pthread_mutex_unlock(philo->meal_check);
	return (ans);
}

bool	ft_philo_isfull(t_philo *philo)
{
	bool	ans;

	pthread_mutex_lock(philo->meal_check);
	ans = philo->eaten >= philo->min_eat;
	pthread_mutex_unlock(philo->meal_check);
	return (ans);
}
