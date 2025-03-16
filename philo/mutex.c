/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:54:45 by mmoulati          #+#    #+#             */
/*   Updated: 2025/03/15 21:20:18 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

t_mutex	*ft_mutex_new(void)
{
	t_mutex	*mutex;

	mutex = malloc(sizeof(t_mutex));
	if (mutex == NULL)
		return (NULL);
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

void	ft_mutex_destroy(t_mutex **mutex)
{
	pthread_mutex_unlock(*mutex);
	pthread_mutex_destroy(*mutex);
	free(*mutex);
	*mutex = NULL;
}
