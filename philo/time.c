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

int		ft_philo_isdead(t_philo *philo);

long	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_msleep(t_philo *philo, long ms)
{
	long	curr;

	curr = ft_timestamp();
	while ((ft_timestamp() - curr) < ms)
	{
		if (ft_philo_isdead(philo))
			return ;
		usleep(100);
	}
}
