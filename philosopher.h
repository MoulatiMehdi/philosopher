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
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_fork;

typedef enum e_state
{
	STATE_DYING,
	STATE_THINKING,
	STATE_EATING
}						t_state;

typedef struct s_philo
{
	long				id;
	long				last_meal;
	t_state				state;
	pthread_t			thread;
	t_fork				*fork_left;
	t_fork				*fork_right;
}						t_philo;

typedef struct s_table
{
	long				time_sleep;
	long				time_eat;
	long				time_die;
	long				min_eat;
	t_philo				**philosophers;
	t_fork				**forks;
}						t_table;

long					ft_timestamp(void);

t_philo					*ft_philosopher_new(void);
t_philo					**ft_philosophers_new(long n);

t_fork					**ft_forks_new(long n);
t_table					*ft_table_new(int argc, char **argv);

#endif
