#include "philosopher.h"
#include <stdlib.h>
#include <string.h>

pthread_mutex_t	**ft_forks_new(long n)
{
	pthread_mutex_t	**forks;
	long			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t *) * (n + 1));
	if (forks == NULL)
		return (NULL);
	memset(forks, 0, sizeof(pthread_mutex_t *) * (n + 1));
	while (i < n)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (forks[i] == NULL)
		{
			while (i >= 0)
			{
				free(forks[i]);
				i--;
			}
			free(forks);
			return (NULL);
		}
	}
	return (forks);
}
