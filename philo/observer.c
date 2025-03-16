/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:24:28 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 21:04:08 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	ft_observer_dead(t_table *table)
{
	size_t	i;

	i = 0;
	while (table->philosophers[i])
	{
		if (ft_philo_isdead(table->philosophers[i]))
		{
			ft_message(table->philosophers[i], "\033[1;91mdied\033[0m");
			return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_observer_ate(t_table *table)
{
	size_t	i;

	if (!table->eat_check)
		return (false);
	i = 0;
	while (table->philosophers[i])
	{
		if (!ft_philo_isfull(table->philosophers[i]))
			return (false);
		i++;
	}
	return (true);
}

void	*ft_observer_should_stop(void *arg)
{
	t_table	*table;

	table = arg;
	while (1)
	{
		if (ft_observer_dead(table) || ft_observer_ate(table))
		{
			pthread_mutex_lock(table->lock_dead);
			table->stop = true;
			pthread_mutex_unlock(table->lock_dead);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
