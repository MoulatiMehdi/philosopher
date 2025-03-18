#include "philo.h"
#include <pthread.h>

void ft_philo_init(t_philo * philo,t_fork **forks,t_args * args)
{
    philo->args = args;
    philo->meal_last = 0;
    philo->meal_count = 0;
    philo->is_ltaken = 0;
    philo->is_rtaken = 0;
    philo->fork_right = &(*forks)[philo->id];
    philo->fork_left = &(*forks)[(philo->id + 1) % args->size];
    philo->fork_right->used = 0;
    pthread_mutex_init(&philo->lock_meal, NULL);
    pthread_mutex_init(&philo->fork_right->lock, NULL);
}

int ft_philos_init(t_philo **philos,t_fork **forks ,t_args *args)
{
    int id;
    *philos = malloc(sizeof(t_philo) * args->size);
    if(*philos == NULL)
        return 0;
    *forks = malloc(sizeof(t_fork) * args->size);
    if(*forks == NULL)
    {
        free(*philos);
        return 0;
    }
    id = 0;
    while(id < args->size)
    {
        (*philos)[id].id = id;
        ft_philo_init(&(*philos)[id],forks,args);
        id++;
    }
    return 1;
}


void ft_free_memory(t_philo * philo,t_fork * fork)
{
    free(philo);
    free(fork);
}
