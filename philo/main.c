#include "philo.h"
#include <pthread.h>
#include <string.h>

void ft_mutexes_init(t_mutex *forks,t_data *data)
{
    int i;

    i = 0;
    while(i < data->size)
    {
        ft_mutex_init(&forks[i], 0);
        i++;
    }
    ft_mutex_init(&data->death, 0);
    ft_mutex_init(&data->write, 0);
    
}

void ft_mutexes_destroy(t_mutex * forks,t_data * data)
{
    int i;

    i = 0;
    while(i < data->size)
    {
        pthread_mutex_destroy(&forks[i].lock);
        i++;
    }
    ft_mutex_destroy(&data->death);
    ft_mutex_destroy(&data->write);
}

void ft_philos_init(t_philo *philos,t_mutex * forks,t_data * data)
{
    long id;

    id = 0;
    ft_time_set(&data->time_start);
    while(id < data->size)
    {
        philos[id].id = id;
        philos[id].data = data;
        philos[id].count = 0;

        philos[id].fork_l= &forks[id];
        philos[id].fork_r= &forks[(id + 1) % data->size];
        if(id % 2 == 1)
        {
            philos[id].fork_r= &forks[id];
            philos[id].fork_l= &forks[(id + 1) % data->size];
        }
        ft_mutex_init(&philos[id].meal, data->time_start);
        id ++;
    }
}

int main(int argc, char *argv[])
{
    t_data data;
    t_mutex forks[PHILO_MAX];
    t_philo philos[PHILO_MAX];

    memset(&data, 0, sizeof(data)); 
    if(ft_data_init(&data,argc,argv))
        return 1;
    ft_mutexes_init(forks, &data);
    ft_philos_init(philos,forks,&data);
    ft_threads_simulation(philos,&data);
    ft_mutexes_destroy(forks,&data);
    return 0;
}
