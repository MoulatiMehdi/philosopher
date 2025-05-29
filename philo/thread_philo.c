/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:11 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/19 20:05:33 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	ft_philo_isdead(t_philo *philo)
{
	int	isdead;

	pthread_mutex_lock(&philo->args->lock_death);
	isdead = philo->args->is_dead;
	pthread_mutex_unlock(&philo->args->lock_death);
	return (isdead);
}

void	*ft_philo_logs(t_philo *philo, char *str)
{
	long	curr;

	curr = ft_timestamp() - philo->args->time_start;
	pthread_mutex_lock(&philo->args->lock_write);
	if (!ft_philo_isdead(philo))
		printf("%013ld %d %s\n", curr, philo->id + 1, str);
	pthread_mutex_unlock(&philo->args->lock_write);
	return (NULL);
}

void	ft_philo_forks_take(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	ft_philo_logs(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_right);
	ft_philo_logs(philo, "has taken a fork");
}

void	ft_philo_forks_put(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	ft_philo_logs(philo, "is sleeping");
	ft_msleep(philo,philo->args->time_sleep);
	ft_philo_logs(philo, "is thinking");
    usleep(500);
}

void	*ft_thread_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->args->size == 1)
		return (ft_philo_logs(philo, "has taken a fork"));
	while (!ft_philo_isdead(philo))
	{
		if (philo->meal_count >= philo->args->meal_min
			&& philo->args->meal_min > 0)
			break ;
		ft_philo_forks_take(philo);
		pthread_mutex_lock(&philo->lock_meal);
		philo->meal_last = ft_timestamp() - philo->args->time_start;
		philo->meal_count++;
		ft_philo_logs(philo, "is eating");
		pthread_mutex_unlock(&philo->lock_meal);
		ft_msleep(philo,philo->args->time_eat);
		ft_philo_forks_put(philo);
	}
	return (NULL);
}
