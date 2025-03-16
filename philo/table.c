/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:56:18 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 21:00:59 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdlib.h>

void	ft_table_philosophers(t_table *table)
{
	size_t	i;
	size_t	n;

	n = table->size;
	i = 0;
	while (i < n)
	{
		table->philosophers[i]->fork_left = table->forks[i];
		table->philosophers[i]->fork_right = table->forks[(n + i - 1) % n];
		table->philosophers[i]->meal_check = table->meals[i];
		table->philosophers[i]->lock_dead = table->lock_dead;
		table->philosophers[i]->min_eat = table->min_eat;
		table->philosophers[i]->time_eat = table->time_eat;
		table->philosophers[i]->time_die = table->time_die;
		table->philosophers[i]->time_sleep = table->time_sleep;
		table->philosophers[i]->stop = &table->stop;
		table->philosophers[i]->last_meal = 0;
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
	table->time_die = atol(argv[2]);
	table->time_eat = atol(argv[3]);
	table->time_sleep = atol(argv[4]);
	table->stop = false;
	table->min_eat = 0;
	table->philosophers = ft_philosophers_new(table->size);
	table->forks = ft_forks_new(table->size);
	table->meals = ft_forks_new(table->size);
	table->lock_dead = ft_mutex_new();
	table->lock_write = ft_mutex_new();
	table->eat_check = argc == 6;
	if (argc == 6)
		table->min_eat = atol(argv[5]);
	ft_table_philosophers(table);
	return (table);
}

void	ft_table_destroy(t_table **table)
{
	ft_forks_destroy(&(*table)->forks);
	ft_forks_destroy(&(*table)->meals);
	ft_philosophers_destroy(&(*table)->philosophers);
	ft_mutex_destroy(&(*table)->lock_dead);
	free(*table);
	*table = NULL;
}
