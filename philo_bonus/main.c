/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:58:59 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/21 20:48:30 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*philos;

	if (!ft_args_init(&args, argc, argv))
		return (EXIT_FAILURE);
	if (!ft_philos_init(&philos, &args))
		return (EXIT_FAILURE);
	if (!ft_process_start(&philos, &args))
		ft_process_stop(&philos, &args);
	ft_process_wait(&philos, &args);
	ft_philos_destroy(philos, &args);
	return (EXIT_SUCCESS);
}
