/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:46:15 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 21:18:17 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H

# include "pthread.h"
# include <bits/pthreadtypes.h>
# include <bits/types/struct_timeval.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	bool				*stop;
	size_t				id;
	size_t				min_eat;
	size_t				eaten;
	size_t				last_meal;
	size_t				time_sleep;
	size_t				time_eat;
	size_t				time_die;
	bool				iseating;
	t_mutex				*fork_left;
	t_mutex				*fork_right;
	t_mutex				*meal_check;
	t_mutex				*lock_dead;
	pthread_t			thread;
}						t_philo;

typedef struct s_table
{
	bool				stop;
	bool				eat_check;
	size_t				size;
	size_t				min_eat;
	size_t				time_sleep;
	size_t				time_eat;
	size_t				time_die;
	t_philo				**philosophers;
	t_mutex				**forks;
	t_mutex				**meals;
	t_mutex				*lock_dead;
	t_mutex				*lock_write;
}						t_table;

size_t					ft_timestamp(void);
int						ft_msleep(size_t msec);

t_philo					*ft_philosopher_new(void);
t_philo					**ft_philosophers_new(size_t n);

t_mutex					*ft_mutex_new(void);
t_mutex					**ft_forks_new(size_t n);

void					ft_forks_destroy(t_mutex ***fork);
void					ft_mutex_destroy(t_mutex **mutex);
void					ft_philosopher_destroy(t_philo **philosopher);
void					ft_philosophers_destroy(t_philo ***philosophers);

t_table					*ft_table_new(int argc, char **argv);

void					ft_forks_put(t_philo *philosopher);
void					ft_forks_take(t_philo *philosopher);

void					ft_philo_eat(t_philo *philosopher);
void					ft_philo_sleep(t_philo *philosopher);
void					ft_philo_think(t_philo *philosopher);

bool					ft_philo_isdead(t_philo *philo);
bool					ft_philo_isfull(t_philo *philo);

void					ft_philo_die(t_philo *philosopher);
void					*ft_observer_should_stop(void *table);
void					*func(void *arg);

void					ft_threads_create(pthread_t *observer, t_table *table);

void					ft_message(t_philo *philosopher, char *str);
void					ft_table_destroy(t_table **table);
void					ft_threads_wait(pthread_t *observer, t_table *table);
#endif
