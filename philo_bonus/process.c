/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:29:41 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/30 18:29:42 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	ft_process_start(t_philo philos[PHILO_MAX], t_args *args)
{
	int		i;
	t_philo	*philo;

	args->time_start = ft_timestamp();
	i = 0;
	while (i < args->size)
	{
		philo = &philos[i];
		philo->pid = fork();
		if (philo->pid < 0)
			return (0);
		if (philo->pid == 0)
		{
			ft_process_philo(philo);
			exit(0);
		}
		i++;
	}
	if (pthread_create(&(args->death), NULL, ft_thread_philos_kill, philos))
		return (0);
	return (1);
}

int	ft_process_wait(t_philo philo[PHILO_MAX], t_args *args)
{
	int	i;
	int	status;

	status = 1;
	i = 0;
	pthread_join(args->death, NULL);
	while (i < args->size)
	{
		if (waitpid(philo[i].pid, NULL, 0) == -1)
			status = 0;
		i++;
	}
	return (status);
}

int	ft_process_stop(t_philo philos[PHILO_MAX], t_args *args)
{
	int	curr;

	curr = 0;
	while (curr < args->size)
	{
		kill(philos[curr].pid, SIGKILL);
		curr++;
	}
	return (1);
}
