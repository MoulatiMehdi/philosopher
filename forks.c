/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:45:47 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/14 19:45:49 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_fork	**ft_forks_new(long n)
{
	t_fork	**forks;
	long	i;

	forks = malloc(sizeof(t_fork *) * n);
	if (forks == NULL)
		return (NULL);
	memset(forks, 0, sizeof(t_fork *) * n);
	i = 0;
	while (i < n)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (forks[i] == NULL)
		{
			while (i >= 0)
			{
				free(forks[i]);
				i--;
			}
			free(forks);
			return (NULL);
		}
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (forks);
}

void	ft_fork_take(t_fork *fork, size_t id)
{
	pthread_mutex_lock(fork);
	printf("%ld %ld has taken a fork\n", ft_timestamp(), id);
}

void	ft_fork_put(t_fork *fork)
{
	pthread_mutex_unlock(fork);
}
