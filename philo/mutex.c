#include "philo.h"

long ft_mutex_get(t_mutex * mutex)
{
    long value;
    pthread_mutex_lock(&mutex->lock);
    value = mutex->value;
    pthread_mutex_unlock(&mutex->lock);

    return value;
}

void ft_mutex_set(t_mutex * mutex,long value)
{
    pthread_mutex_lock(&mutex->lock);
    mutex->value = value;
    pthread_mutex_unlock(&mutex->lock);
}

void ft_mutex_add(t_mutex * mutex,long value)
{
    pthread_mutex_lock(&mutex->lock);
    mutex->value += value;
    pthread_mutex_unlock(&mutex->lock);

}

void ft_mutex_init(t_mutex * mutex,long value)
{
    mutex->value = value;
    pthread_mutex_init(&mutex->lock,NULL);
}

void ft_mutex_destroy(t_mutex * mutex)
{
    pthread_mutex_destroy(&mutex->lock);
}
