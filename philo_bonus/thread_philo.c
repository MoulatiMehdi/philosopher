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
#include <semaphore.h>

int	ft_philo_isdead(t_philo *philo)
{
	int	isdead;

	sem_wait(philo->args->lock_death);
	isdead = philo->args->is_dead;
	sem_post(philo->args->lock_death);
	return (isdead);
}

void	*ft_philo_logs(t_philo *philo, char *str)
{
	long	curr;

	curr = ft_timestamp() - philo->args->time_start;
	sem_wait(philo->args->lock_write);
	if (!ft_philo_isdead(philo))
		printf("%013ld %d %s\n", curr, philo->id + 1, str);
	sem_post(philo->args->lock_write);
	return (NULL);
}

void	ft_philo_fork_take(t_philo *philo)
{
	t_fork	*fork;

	if (ft_philo_isdead(philo))
		return ;
	sem_wait(philo->args->lock_forks);
	ft_philo_logs(philo, "has taken a fork");
	sem_wait(philo->args->lock_forks);
	ft_philo_logs(philo, "has taken a fork");
}

void	ft_philo_forks_put(t_philo *philo)
{
	sem_post(philo->args->lock_forks);
	sem_post(philo->args->lock_forks);
	ft_philo_logs(philo, "is sleeping");
	ft_msleep(philo->args->time_sleep);
	ft_philo_logs(philo, "is thinking");
}

void	*ft_thread_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->args->size == 1)
		return (ft_philo_logs(philo, "has taken a fork"));
	if (philo->id % 2 != 0)
		ft_msleep(philo->args->time_eat);
	while (!ft_philo_isdead(philo))
	{
		if (philo->meal_count >= philo->args->meal_min
			&& philo->args->meal_min > 0)
			break ;
		ft_philo_fork_take(philo);
		sem_wait(&philo->lock_meal);
		philo->meal_last = ft_timestamp() - philo->args->time_start;
		sem_post(&philo->lock_meal);
		ft_philo_logs(philo, "is eating");
		ft_msleep(philo->args->time_eat);
		philo->meal_count++;
		ft_philo_forks_put(philo);
	}
	return (NULL);
}
