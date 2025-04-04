#include "philo.h"

void ft_philo_fork_take(t_philo * philo,t_mutex * mutex)
{
    pthread_mutex_lock(&mutex->lock);
    mutex->value = 1; 
    ft_time_log(philo, MSG_FORK);
}

void ft_philo_fork_put(t_mutex * mutex)
{
    mutex->value = 0; 
    pthread_mutex_unlock(&mutex->lock);
}
void ft_philo_eat(t_philo * philo)
{
    long time;

    ft_philo_fork_take(philo, philo->fork_l);
    ft_philo_fork_take(philo, philo->fork_r);

    ft_time_set(&time);
    ft_time_log(philo, MSG_EAT);
    philo->count ++;
    ft_mutex_set(&philo->meal,time);
    ft_time_sleep(philo, philo->data->time_eat);

}

void ft_philo_sleep(t_philo * philo)
{
    int is_finished =  philo->count >= philo->data->meal_min && philo->data->meal_min >= 0;

    if(!is_finished)
        ft_time_log(philo, MSG_SLEEP);
    ft_philo_fork_put( philo->fork_r);
    ft_philo_fork_put( philo->fork_l);
    
    if(is_finished)
        return ;
    ft_time_sleep(philo, philo->data->time_sleep);
    ft_time_log(philo, MSG_THINK);
}


