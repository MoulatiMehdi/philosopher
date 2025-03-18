#include "philo.h"
#include <pthread.h>

void * ft_thread_philo(void * arg)
{
    t_philo * philo = arg;
    return NULL;
}

void * ft_thread_monitor(void * arg)
{

    t_philo ** philos = arg;
    return NULL;
}

int ft_threads_start(t_philo **philo,t_args * args)
{
    int i;
    
    args->time_start = ft_timestamp();
    i = 0;
    while(i < args->size)
    {
        if(pthread_create(&(*philo)[i].thread, NULL,ft_thread_philo ,NULL))
            return 0;
        i++;
    }
    if(pthread_create(&(args->monitor),NULL,ft_thread_monitor,NULL))
        return 0;
    return 1;
}

int ft_threads_wait(t_philo **philo,t_args * args)
{
    int i;
    int status;

    status = 1;
    i = 0;
    while(i < args->size)
    {
        if(pthread_join((*philo)[i].thread, NULL))
            status = 0;
        i++;
    }
    return status;
}
