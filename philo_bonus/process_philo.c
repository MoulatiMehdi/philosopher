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

static void	*ft_philo_logs(t_philo *philo, char *str)
{
	long	curr;

	curr = ft_timestamp() - philo->args->time_start;
	sem_wait(philo->args->lock_write);
	printf("%013ld %d %s\n", curr, philo->id + 1, str);
	sem_post(philo->args->lock_write);
	return (NULL);
}

static void	ft_philo_fork_take(t_philo *philo)
{
	sem_wait(philo->args->lock_forks);
	ft_philo_logs(philo, "has taken a fork");
}

static void	ft_philo_forks_put(t_philo *philo)
{
	sem_post(philo->args->lock_forks);
	sem_post(philo->args->lock_forks);
	ft_philo_logs(philo, "is sleeping");
	ft_msleep(philo->args->time_sleep);
	ft_philo_logs(philo, "is thinking");
}

void	*ft_process_philo(t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, ft_thread_monitor, philo);
	if (philo->id % 2 != 0)
		ft_msleep(philo->args->time_eat);
	while (1)
	{
		if (philo->meal_count >= philo->args->meal_min
			&& philo->args->meal_min > 0)
			break ;
		ft_philo_fork_take(philo);
		ft_philo_fork_take(philo);
		sem_wait(philo->lock_meal);
		philo->meal_last = ft_timestamp() - philo->args->time_start;
		sem_post(philo->lock_meal);
		ft_philo_logs(philo, "is eating");
		ft_msleep(philo->args->time_eat);
		philo->meal_count++;
		ft_philo_forks_put(philo);
	}
	sem_post(philo->args->lock_death);
	return (NULL);
}
