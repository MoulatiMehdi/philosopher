/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:11 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/21 21:31:10 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	ft_philo_fork_take(char c, t_philo *philo)
{
	t_fork	*fork;

	if (ft_philo_isdead(philo))
		return ;
	fork = philo->fork_right;
	if (c == 'l')
		fork = philo->fork_left;
	pthread_mutex_lock(fork);
	ft_philo_logs(philo, "has taken a fork");
}

void	ft_philo_forks_put(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	ft_philo_logs(philo, "is sleeping");
	ft_msleep(philo->args->time_sleep);
	ft_philo_logs(philo, "is thinking");
}

void	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(&philo->lock_meal);
	philo->meal_last = ft_timestamp() - philo->args->time_start;
	pthread_mutex_unlock(&philo->lock_meal);
	ft_philo_logs(philo, "is eating");
	pthread_mutex_lock(&philo->lock_counter);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->lock_counter);
	ft_msleep(philo->args->time_eat);
}

void	*ft_thread_philo(void *arg)
{
	t_philo	*philo;
	int		count;

	philo = arg;
	if (philo->args->size == 1)
		return (ft_philo_logs(philo, "has taken a fork"));
	// if (philo->id % 2 != 0)
	// 	ft_msleep(philo->args->time_eat);
	while (!ft_philo_isdead(philo))
	{
		pthread_mutex_lock(&philo->lock_counter);
		count = philo->meal_count;
		pthread_mutex_unlock(&philo->lock_counter);
		if (count >= philo->args->meal_min && philo->args->meal_min > -1)
			break ;
		// ft_philo_fork_take('r', philo);
		// ft_philo_fork_take('l', philo);
		ft_philo_eat(philo);
		ft_philo_forks_put(philo);
	}
	return (NULL);
}
