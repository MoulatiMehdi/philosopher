/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:45:47 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 22:06:08 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_mutex	**ft_forks_new(size_t n)
{
	t_mutex	**forks;
	size_t	i;

	forks = malloc(sizeof(t_mutex *) * (n + 1));
	if (forks == NULL)
		return (NULL);
	forks[n] = NULL;
	i = 0;
	while (i < n)
	{
		forks[i] = ft_mutex_new();
		if (forks[i] == NULL)
		{
			ft_forks_destroy(&forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

void	ft_forks_take(t_philo *philosopher)
{
	t_mutex	*mutex_l;
	t_mutex	*mutex_r;

	mutex_l = philosopher->fork_left;
	mutex_r = philosopher->fork_right;
	if (philosopher->id % 2 != 0)
	{
		mutex_l = philosopher->fork_right;
		mutex_r = philosopher->fork_left;
	}
	pthread_mutex_lock(mutex_l);
	ft_message(philosopher, "has taken a fork");
	pthread_mutex_lock(mutex_r);
	ft_message(philosopher, "has taken a fork");
}

void	ft_forks_put(t_philo *philosopher)
{
	t_mutex	*mutex_l;
	t_mutex	*mutex_r;

	mutex_l = philosopher->fork_left;
	mutex_r = philosopher->fork_right;
	if (philosopher->id % 2 != 0)
	{
		mutex_l = philosopher->fork_right;
		mutex_r = philosopher->fork_left;
	}
	pthread_mutex_unlock(mutex_l);
	pthread_mutex_unlock(mutex_r);
}

void	ft_forks_destroy(t_mutex ***forks)
{
	size_t	i;

	if (forks == NULL || *forks == NULL)
		return ;
	i = 0;
	while ((*forks)[i])
	{
		ft_mutex_destroy(&(*forks)[i]);
		i++;
	}
	free(*forks);
	*forks = NULL;
}
