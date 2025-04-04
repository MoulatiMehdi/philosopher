#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>


void ft_time_set(long * usec)
{
    t_time time; 
   gettimeofday(&time, NULL); 
   * usec =  time.tv_sec * 1000000 + time.tv_usec;
}


void ft_message(t_philo * philo,char * str)
{
    long time;

    ft_time_set(&time);
    pthread_mutex_lock(&philo->data->write.lock);
    printf("%013ld %3ld %s\n",(time - philo->data->time_start) / 1000 ,philo->id + 1,str);    
    pthread_mutex_unlock(&philo->data->write.lock);
}

void ft_time_log(t_philo * philo,char * str)
{
    if(ft_mutex_get(&philo->data->death) == 1)
        return ;
    ft_message(philo,str);
}

void ft_time_sleep(t_philo * philo,long miliseconds)
{
    long curr;
    long start;

    ft_time_set(&start);
    while(1)
    {
        ft_time_set(&curr);
        if(curr - start > miliseconds * 1000)
            return ;
        if(ft_mutex_get(&philo->data->death))
            return ;
        usleep(100);
    }
}
