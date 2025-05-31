/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:59:08 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/19 00:17:43 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int ft_monitor_meal(t_philo * philo,t_args * args)
{
	long	last_meal;
    long i;

    i = 0;
    while(i < args->size)
    {
        sem_wait(philo[i].lock_meal);
        last_meal = philo[i].meal_count;
        sem_post(philo[i].lock_meal);
        if (last_meal < args->meal_min)
            return 0;
    }
    printf("meal has been eating\n");
    sem_wait(args->lock_write);
    sem_post(args->lock_death);
    return 1;
}

int ft_monitor_death(t_philo * philo,t_args * args)
{
	long	time_curr;
	long	last_meal;
    long i;

    i = 0;
	time_curr = ft_timestamp() - args->time_start;
    while(i < args->size)
    {
        sem_wait(philo[i].lock_meal);
        last_meal = time_curr - philo[i].meal_last;
        sem_post(philo[i].lock_meal);
        if (last_meal > args->time_die)
        {
            sem_wait(args->lock_write);
            printf("%013ld %d died\n", time_curr, philo[i].id + 1);
            sem_post(args->lock_death);
            return 1;
        }
    }
    return 0;
}

void	*ft_thread_monitor(void *arg)
{
	t_philo	*philo;
	t_args	*args;
    
	philo = arg;
	args = philo->args;

    while (1)
	{
        if(ft_monitor_meal(philo, args))
            break;
        if(ft_monitor_death(philo, args))
            break;
		usleep(500);
	}
	return (NULL);
}

void	*ft_thread_philos_kill(void *arg)
{
	t_philo	*philos;
	t_args	*args;

	philos = arg;
	args = philos[0].args;
	sem_wait(args->lock_death);
	ft_process_stop(philos, args);
	return (NULL);
}
