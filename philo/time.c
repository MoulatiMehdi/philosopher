/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:33 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/18 23:59:33 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_msleep(long ms)
{
	long	curr;

	curr = ft_timestamp();
	while ((ft_timestamp() - curr) < ms)
		usleep(100);
}

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
