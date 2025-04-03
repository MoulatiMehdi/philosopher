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

# include "unistd.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define PHILO_MAX 200

typedef pthread_mutex_t	t_mutex;
typedef pthread_mutex_t	t_fork;

typedef struct s_data
{
    int					size;
    int					time_eat;
    int					time_die;
    int					time_sleep;
    long				time_start;
    int					is_dead;
    int					meal_min;
    t_mutex				lock_write;
    t_mutex				lock_death;
    pthread_t			monitor;
}						t_data;

typedef struct s_philo
{
    int					id;
    int					meal_count;
    long				meal_last;
    t_mutex				lock_meal;
    t_fork				*fork_r;
    t_fork				*fork_l;
    t_data				*data ;
    pthread_t			thread;
}						t_philo;


long					ft_atoi(const char *str);
int ft_threads_create(t_data * data,t_fork * forks);
#endif // !PHILO_H
