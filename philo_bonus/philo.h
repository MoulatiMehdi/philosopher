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
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>

# define PHILO_MAX 300
# define SEM_FORK "/sem_fork"
# define SEM_END "/sem_end"
# define SEM_WRITE "/sem_write"
# define SEM_MEAL "/sem_write"

typedef pthread_mutex_t	t_fork;

typedef struct s_args
{
	int					size;
	int					time_eat;
	int					time_die;
	int					meal_min;
	int					time_sleep;
	long				time_start;
	sem_t				*lock_forks;
	sem_t				*lock_write;
	sem_t				*lock_death;
	pthread_t			death;
}						t_args;

typedef struct s_philo
{
	int					id;
	int					meal_count;
	long				meal_last;
	t_args				*args;
	sem_t				*lock_meal;
	pid_t				pid;
}						t_philo;

int						ft_philos_init(t_philo **philos, t_args *args);
void					ft_philos_destroy(t_philo *philos, t_args *args);

void					ft_msleep(long miliseconds);
long					ft_timestamp(void);

int						ft_process_stop(t_philo **philos, t_args *args);
int						ft_process_start(t_philo **philo, t_args *args);
int						ft_process_wait(t_philo **philo, t_args *args);

void					*ft_process_philo(t_philo *philo);
void					*ft_thread_monitor(void *arg);
int						ft_args_init(t_args *args, int argc, char **argv);
void					*ft_philo_kill(void *arg);

void					*ft_thread_philos_kill(void *arg);
#endif // !PHILO_H
