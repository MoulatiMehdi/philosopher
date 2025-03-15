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

	i = 0;
	forks = malloc(sizeof(t_fork *) * (n + 1));
	if (forks == NULL)
		return (NULL);
	memset(forks, 0, sizeof(t_fork *) * (n + 1));
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
	    i++;
    }
	return (forks);
}
