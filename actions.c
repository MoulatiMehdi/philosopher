#include "philosopher.h"

void	ft_philo_eat(t_philo *philosopher)
{
	ft_fork_take(philosopher->fork_left, philosopher->id);
	ft_fork_take(philosopher->fork_right, philosopher->id);
	philosopher->last_meal = ft_timestamp();
	philosopher->state = EATING;
	printf("%ld %ld is eating\n", philosopher->last_meal, philosopher->id);
	ft_msleep(philosopher->time_eat);
	ft_fork_put(philosopher->fork_left);
	ft_fork_put(philosopher->fork_right);
}

void	ft_philo_sleep(t_philo *philosopher)
{
	philosopher->state = SLEEPING;
	printf("%ld %ld is sleeping\n", ft_timestamp(), philosopher->id);
	ft_msleep(philosopher->time_sleep);
}

void	ft_philo_think(t_philo *philosopher)
{
	philosopher->state = THINKING;
	printf("%ld %ld is thinking\n", ft_timestamp(), philosopher->id);
}

void	ft_philo_die(t_philo *philosopher)
{
	philosopher->state = THINKING;
	printf("%ld %ld is dead\n", ft_timestamp(), philosopher->id);
}
