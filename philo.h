#ifndef PHILO_H

# define PHILO_H

# include "unistd.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define PHILO_MAX 300

typedef pthread_mutex_t	t_mutex;

typedef struct s_args
{
	int					size;
	int					time_eat;
	int					time_die;
	int					meal_min;
	int					time_sleep;
	int					is_dead;
	long				time_start;
	t_mutex				lock_write;
	t_mutex				lock_death;
	pthread_t			monitor;
}						t_args;

typedef struct s_fork
{
	int					used;
	t_mutex				lock;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					is_ltaken;
	int					is_rtaken;
	long				meal_last;
	int					meal_count;
	t_mutex				lock_meal;
	t_fork				*fork_right;
	t_fork				*fork_left;
	t_args				*args;
	pthread_t			thread;
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
