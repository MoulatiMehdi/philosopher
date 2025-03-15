/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:46:15 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/14 21:44:24 by mmoulati         ###   ########.fr       */
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

typedef pthread_mutex_t	t_fork;

typedef enum e_action
{
	EATING,
	THINKING,
	SLEEPING
}						t_state;

typedef struct s_philo
{
	size_t				id;
	long				min_eat;
	size_t				eaten;
	size_t				last_meal;
	size_t				time_sleep;
	size_t				time_eat;
	size_t				time_die;
	pthread_t			thread;
	t_state				state;
	t_fork				*fork_left;
	t_fork				*fork_right;
	bool				*stop;
}						t_philo;

typedef struct s_table
{
	size_t				min_eat;
	size_t				time_sleep;
	size_t				time_eat;
	size_t				time_die;
	t_philo				**philosophers;
	t_fork				**forks;
	long				size;
	bool				stop;
}						t_table;

size_t					ft_timestamp(void);
int						ft_msleep(size_t msec);

t_philo					*ft_philosopher_new(void);
t_philo					**ft_philosophers_new(long n);

t_fork					**ft_forks_new(long n);

void					ft_fork_take(t_fork *fork, size_t id);
void					ft_fork_put(t_fork *fork);

t_table					*ft_table_new(int argc, char **argv);

void					ft_philo_fork_take(t_philo *philosopher, t_fork *fork);
void					ft_philo_fork_put(t_fork *fork);
void					ft_philo_eat(t_philo *philosopher);
void					ft_philo_sleep(t_philo *philosopher);
void					ft_philo_think(t_philo *philosopher);

#endif
