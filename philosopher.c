/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:46:06 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/14 19:46:08 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*ft_philosopher_new(void)
{
	static int	id = 1;
	t_philo		*philosopher;

	philosopher = malloc(sizeof(t_philo));
	if (philosopher == NULL)
		return (NULL);
	philosopher->id = id;
	philosopher->state = STATE_THINKING;
	philosopher->last_meal = 0;
	philosopher->fork_left = NULL;
	philosopher->fork_right = NULL;
	id++;
	return (philosopher);
}

t_philo	**ft_philosophers_new(long n)
{
	long	i;
	t_philo	**philosophers;

	philosophers = malloc(sizeof(t_philo *) * (n + 1));
	if (philosophers == NULL)
		return (NULL);
	memset(philosophers, 0, sizeof(t_philo *) * (n + 1));
	i = 0;
	while (i < n)
	{
		philosophers[i] = ft_philosopher_new();
		i++;
	}
	return (philosophers);
}
