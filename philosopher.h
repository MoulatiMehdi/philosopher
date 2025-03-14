#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H
# include "pthread.h"
# include <bits/pthreadtypes.h>
# include <bits/types/struct_timeval.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef enum e_state
{
	STATE_DYING,
	STATE_THINKING,
	STATE_EATING
}					t_state;

typedef struct s_philo
{
	long			id;
	long			last_meal;
	t_state			state;
	pthread_t		th;
}					t_philo;

typedef struct s_data
{
	long			time_sleep;
	long			time_eat;
	long			time_die;
	long			min_eat;
	t_philo			**philosophers;
	pthread_mutex_t	**forks;
}					t_data;

long				ft_timestamp(void);

t_philo				*ft_philosopher_new(void);
t_philo				**ft_philosophers_new(long n);
#endif // !
