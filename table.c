/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:56:18 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/14 19:56:18 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdlib.h>

void	ft_table_init(t_table *table)
{
	long	i;
    long n;

    n = table->size;
	table->philosophers = ft_philosophers_new(n);
	table->forks = ft_forks_new(n);
	i = 0;
	while (i < n)
	{
		table->philosophers[i]->fork_left = table->forks[(n + i - 1) % n];
		table->philosophers[i]->fork_right = table->forks[(n + i + 1) % n];
		table->philosophers[i]->min_eat = table->min_eat;
		table->philosophers[i]->time_eat = table->time_eat;
		table->philosophers[i]->time_die = table->time_die;
		table->philosophers[i]->time_sleep = table->time_sleep;
        i++;
	}
}

t_table	*ft_table_new(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->size = atol(argv[1]);
    ft_table_init(table);
	table->time_die = atol(argv[2]);
	table->time_eat = atol(argv[3]);
	table->time_sleep = atol(argv[4]);
	table->min_eat = -1;
	if (argc == 6)
		table->min_eat = atol(argv[5]);
	return (table);
}
