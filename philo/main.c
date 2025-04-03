#include "philo.h"
#include <pthread.h>
#include <string.h>

int ft_data_isvalid(t_data  * data)
{
    if(data->meal_min < 0)
        return 0;
    if(data->time_die <= 0)
        return 0;
    if(data->time_sleep <= 0)
        return 0;
    if(data->time_eat <= 0)
        return 0;
    if(data->size <= 0)
        return 0;
    return 1;
}

int ft_data_init(t_data * data,int argc,char ** argv)
{
    if(argc < 5 || argc > 6)
        return 1;
    data->size = ft_atoi(argv[1]);
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    data->meal_min = -1;
    if(argc == 6)
        data->time_die = ft_atoi(argv[5]);
    if(!ft_data_isvalid(data))
        return 1;
    return 0;
}

void ft_mutexes_init(t_fork *forks,t_data *data)
{
    int i;

    i = 0;

    while(i < data->size)
    {
        pthread_mutex_init(&forks[i],NULL);
        i++;
    }
    pthread_mutex_init(&data->lock_death,NULL);
    pthread_mutex_init(&data->lock_write,NULL);
}

void ft_mutexes_destroy(t_fork * forks,t_data * data)
{
    int i;

    i = 0;

    while(i < data->size)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->lock_death);
    pthread_mutex_destroy(&data->lock_write);
}

int main(int argc, char *argv[])
{
    t_data data;
    t_fork forks[PHILO_MAX];

    memset(&data, 0, sizeof(data)); 
    if(ft_data_init(&data,argc,argv))
        return 1;
    ft_mutexes_init(forks, &data);
    ft_threads_create(&data,forks);
    ft_threads_wait(&data);
    ft_mutexes_destroy(forks,&data);
    return 0;
}
