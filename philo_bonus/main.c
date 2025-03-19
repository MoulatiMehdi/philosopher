/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:58:59 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/18 23:59:03 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>
#include <semaphore.h>

#define SEM_FORK "/sem_fork"
#define SEM_END "/sem_end"
#define SEM_WRITE "/sem_write"

int	ft_args_semaphore_init(t_args *args)
{
	sem_unlink(SEM_END);
	sem_unlink(SEM_FORK);
	sem_unlink();
	args->lock_death = sem_open("/sem_death", O_CREAT, 0644, 1);
	args->lock_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	args->lock_forks = sem_open("/sem_fork", O_CREAT, 0644, args->size);
	sem_unlink("/sem_write");
	sem_unlink("/sem_death");
	sem_unlink("/sem_fork");
	sem_wait(args->finished);
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
	args->is_dead = 0;
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
	ft_args_semaphore_init(params);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*philo;
	t_fork	*forks;

	if (!ft_args_init(&args, argc, argv))
		return (EXIT_FAILURE);
	if (!ft_philos_init(&philo, &forks, &args))
		return (EXIT_FAILURE);
	if (!ft_threads_start(&philo, &args))
		ft_threads_stop(&args);
	ft_threads_wait(&philo, &args);
	ft_free_memory(philo, forks);
	return (EXIT_SUCCESS);
}
