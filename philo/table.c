/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:56:18 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/16 23:27:43 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdlib.h>

void	ft_table_philosophers(t_table *table, size_t *num)
{
	size_t	i;
	size_t	n;

	if (table == NULL)
		return ;
	n = table->size;
	i = 0;
	while (i < n)
	{
		table->philosophers[i]->fork_left = table->forks[i];
		table->philosophers[i]->fork_right = table->forks[(n + i - 1) % n];
		if (i % 2 == 0)
		{
			table->philosophers[i]->fork_right = table->forks[i];
			table->philosophers[i]->fork_left = table->forks[(n + i - 1) % n];
		}
		table->philosophers[i]->meal_check = table->meals[i];
		table->philosophers[i]->lock_dead = table->lock_dead;
		table->philosophers[i]->time_die = num[0];
		table->philosophers[i]->time_eat = num[1];
		table->philosophers[i]->time_sleep = num[2];
		table->philosophers[i]->min_eat = num[3];
		table->philosophers[i]->stop = &table->stop;
		table->philosophers[i]->last_meal = 0;
		i++;
	}
}

t_table	*ft_table_new(int argc, char **argv)
{
	t_table	*table;
	size_t	num[6];

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->size = ft_atoi(argv[1]);
	num[0] = ft_atoi(argv[2]);
	num[1] = ft_atoi(argv[3]);
	num[2] = ft_atoi(argv[4]);
	num[3] = 0;
	if (argc == 6)
		num[3] = atol(argv[5]);
	table->stop = false;
	table->philosophers = ft_philosophers_new(table->size);
	table->forks = ft_forks_new(table->size);
	table->meals = ft_forks_new(table->size);
	table->lock_dead = ft_mutex_new();
	table->eat_check = argc == 6;
	if (table->philosophers == NULL || table->meals == NULL
		|| table->forks == NULL || table->lock_dead == NULL)
		ft_table_destroy(&table);
	ft_table_philosophers(table, num);
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
