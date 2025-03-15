/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:45:59 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/14 19:46:36 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void ft_philo_fork_take(t_philo * philosopher)
{
    printf("%ld %ld has taken a fork\n",ft_timestamp(),philosopher->id);
    pthread_mutex_lock(philosopher->fork_left);

    printf("%ld %ld has taken a fork\n",ft_timestamp(),philosopher->id);
    pthread_mutex_lock(philosopher->fork_right);
}

void ft_philo_fork_put(t_philo * philosopher)
{
    pthread_mutex_unlock(philosopher->fork_left);
    pthread_mutex_unlock(philosopher->fork_right);
}

void ft_philo_eat(t_philo * philosopher)
{
    philosopher->last_meal = ft_timestamp();
    printf("%ld %ld is eating\n",philosopher->last_meal,philosopher->id);
    usleep(philosopher->time_eat * 1000); 
}

void ft_philo_sleep(t_philo * philosopher)
{
    printf("%ld %ld is sleeping\n",ft_timestamp(),philosopher->id);
    usleep(philosopher->time_sleep * 1000); 
}

void ft_philo_think(t_philo * philosopher)
{
    printf("%ld %ld is thinking\n",ft_timestamp(),philosopher->id);
}
void * func(void * arg)
{
    t_philo * philosopher = arg;
    
    while(1)
    {
        ft_philo_think(philosopher);
        ft_philo_fork_take(philosopher);
        ft_philo_eat(philosopher);
        ft_philo_fork_put(philosopher); 
        ft_philo_sleep(philosopher);
    }
    return NULL;
}
int	main(int argc, char **argv)
{
	t_table	*table;
    t_philo *philosopher;
    int i;

    if(argc != 5 && argc != 6)
    {
        printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [nbr_of_times_each_philosopher_must_eat]");
        return 0;
    }
	table = ft_table_new(argc, argv);
    i = 0;
    while(i < table->size)
    {
        philosopher = table->philosophers[i];
	    pthread_create(&philosopher->thread, NULL, func, philosopher);
        i++;
    }
    
    i = 0;
    while(i < table->size)
    {
	    pthread_join(table->philosophers[i]->thread, NULL);
        i++;
    }

    return (0);
}
