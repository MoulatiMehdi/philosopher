# include "philo.h"

void * ft_thread_monitor(void * arg)
{
    t_philo * philos;
    t_data * data;
    long time;
    long id;

    philos = arg;
    data = philos[0].data;
    while (ft_mutex_get(&data->death) == 0)
    {
        id = 0; 
        ft_time_set(&time);
        while(id < data->size)
        {
            if((time - ft_mutex_get(&philos[id].meal))/1000 > data->time_die)
            {
                ft_mutex_set(&data->death, 1);
                ft_message(&philos[id], MSG_DIE);
                break;
            }
            id ++;
        }
    }
    return NULL;
}

void * ft_thread_philo(void * arg)
{
    t_philo * philo;

    philo = arg;
    while(ft_mutex_get(&philo->data->death) == 0)
    {
        ft_philo_eat(philo);    
        ft_philo_sleep(philo);    
        if(philo->count >= philo->data->meal_min && philo->data->meal_min >= 0)
            break;
    }
    return NULL;
}


int ft_threads_wait(t_philo * philos,t_data * data)
{
    long id;

    id = 0;
    while (id < data->size)
    {
        pthread_join(philos[id].thread,NULL);
        id++;
    }
    ft_mutex_set(&data->death, 1);
    pthread_join(data->monitor,NULL);
    return 0;
}

int ft_threads_create(t_philo *philos,t_data * data)
{
    long id;

    id = 0;
    while (id < data->size)
    {
        pthread_create(&philos[id].thread,NULL,ft_thread_philo,&philos[id]);
        id++;
    }
    pthread_create(&data->monitor,NULL,ft_thread_monitor,philos);
    return 0;
}

void ft_threads_simulation(t_philo *philos,t_data * data)
{
    ft_threads_create(philos,data);
    ft_threads_wait(philos,data);
}

