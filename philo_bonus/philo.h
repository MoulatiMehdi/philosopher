/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:00:04 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/19 21:21:37 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "unistd.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>

# define PHILO_MAX 300

typedef pthread_mutex_t	t_fork;

typedef struct s_args
{
	int					size;
	int					time_eat;
	int					time_die;
	int					meal_min;
	int					time_sleep;
	long				time_start;
	int					is_dead;
	sem_t				*lock_forks;
	sem_t				*lock_write;
	sem_t				*lock_death;
	pthread_t			monitor;
}						t_args;

typedef struct s_philo
{
	int					id;
	int					meal_count;
	long				meal_last;
	t_args				*args;
	sem_t				lock_meal;
	pid_t				pid;
}						t_philo;

int						ft_philos_init(t_philo **philos, t_fork **forks,
							t_args *args);

void					ft_free_memory(t_philo *philo, t_fork *fork);

void					ft_msleep(long miliseconds);
long					ft_timestamp(void);

int						ft_threads_stop(t_args *args);
int						ft_threads_start(t_philo **philo, t_args *args);
int						ft_threads_wait(t_philo **philo, t_args *args);

void					*ft_thread_philo(void *arg);
void					*ft_thread_monitor(void *arg);

#endif // !PHILO_H
