/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:06 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/19 13:36:50 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

void	ft_philo_init(t_philo *philo, t_args *args)
{
	char	sem_name[30];
	int		i;
	int		num;

	i = 0;
	philo->args = args;
	philo->meal_last = 0;
	philo->meal_count = 0;
	while (SEM_MEAL[i])
	{
		sem_name[i] = SEM_MEAL[i];
		i++;
	}
	num = philo->id;
	while (1)
	{
		sem_name[i] = num % 10;
		i++;
		num /= 10;
		if (num == 0)
			break ;
	}
	sem_unlink(sem_name);
	philo->lock_meal = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
}

int	ft_philos_init(t_philo philos[PHILO_MAX], t_args *args)
{
	int	id;

	id = 0;
	while (id < args->size)
	{
		philos[id].id = id;
		ft_philo_init(&philos[id], args);
		id++;
	}
	return (1);
}

void	ft_philos_destroy(t_philo *philos, t_args *args)
{
    long i;
	sem_close(args->lock_death);
	sem_close(args->lock_write);
	sem_close(args->lock_forks);
    i = args->size;
    while(i < args->size)
    {
        sem_close(philos[i].lock_meal);
        i++;
    }
}
