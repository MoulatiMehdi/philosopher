#include "philo.h"

int	ft_args_semaphore_init(t_args *args)
{
	sem_unlink(SEM_END);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	args->lock_death = sem_open("/sem_death", O_CREAT, 0644, 1);
	args->lock_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	args->lock_forks = sem_open("/sem_fork", O_CREAT, 0644, args->size);
	sem_unlink("/sem_write");
	sem_unlink("/sem_death");
	sem_unlink("/sem_fork");
	sem_wait(args->lock_death);
	return (0);
}

int	ft_args_init(t_args *args, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(1, "Usage : ./philo nbr_philos time_die ", 36);
		write(1, "time_eat time_sleep [nbr_meal]\n", 31);
		return (0);
	}
	args->meal_min = -1;
	args->size = atoi(argv[1]);
	args->time_die = atoi(argv[2]);
	args->time_eat = atoi(argv[3]);
	args->time_sleep = atoi(argv[4]);
	if (argc == 6)
	{
		args->meal_min = atoi(argv[5]);
		if (args->meal_min < 0)
			return (0);
	}
	if (args->size <= 0 || args->size > PHILO_MAX)
		return (0);
	if (args->time_sleep <= 0 || args->time_eat <= 0 || args->time_die <= 0)
		return (0);
	ft_args_semaphore_init(args);
	return (1);
}
