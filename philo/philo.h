/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:00:04 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/20 20:46:58 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <limits.h>

# include <pthread.h>
# include <signal.h>

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define PHILO_MAX  200
# define MSG_THINK  "is thinking"
# define MSG_SLEEP  "is sleeping"
# define MSG_EAT    "is eating"
# define MSG_DIE    "die"
# define MSG_FORK   "has taken a fork"


typedef struct timeval t_time; 

typedef struct s_mutex 
{
    long value;
    pthread_mutex_t lock;
} t_mutex;

typedef struct s_data
{
    long					size;
    long					time_eat;
    long					time_die;
    long					time_sleep;
    long				time_start;
    long				meal_min;
    t_mutex				death;
    t_mutex		write;
    pthread_t			monitor;
}						t_data;

typedef struct s_philo
{
    long					id;
    long				count;
    pthread_t			thread;
    t_data				*data;
    t_mutex				meal;
    t_mutex				*fork_r;
    t_mutex				*fork_l;
}						t_philo;



void ft_threads_simulation(t_philo *philos,t_data * data);

long ft_mutex_get(t_mutex * mutex);
void ft_mutex_set(t_mutex * mutex,long value);
void ft_mutex_add(t_mutex * mutex,long value);
void ft_mutex_init(t_mutex * mutex,long value);
void ft_mutex_destroy(t_mutex * mutex);


void ft_time_set(long * usec);
void ft_time_log(t_philo * philo,char * str);
void ft_time_sleep(t_philo * philo,long miliseconds);
void ft_message(t_philo * philo,char * str);


int ft_data_init(t_data * data,int argc,char ** argv);


void ft_philo_eat(t_philo * philo);
void ft_philo_sleep(t_philo * philo);
#endif // !PHILO_H
