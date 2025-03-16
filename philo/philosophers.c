/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:54:29 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/16 21:13:21 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	**ft_philosophers_new(size_t n)
{
	size_t	i;
	t_philo	**philosophers;

	philosophers = malloc(sizeof(t_philo *) * (n + 1));
	if (philosophers == NULL)
		return (NULL);
	philosophers[n] = NULL;
	i = 0;
	while (i < n)
	{
		philosophers[i] = ft_philosopher_new();
		philosophers[i]->id = i + 1;
		i++;
	}
	return (philosophers);
}

void	ft_philosophers_destroy(t_philo ***philosophers)
{
	size_t	i;

	i = 0;
	if (philosophers == NULL || *philosophers == NULL)
		return ;
	while ((*philosophers)[i])
	{
		ft_philosopher_destroy(&(*philosophers)[i]);
		i++;
	}
	free(*philosophers);
	*philosophers = NULL;
}
