#include "philo.h"

long	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_msleep(long ms)
{

	long	curr;

	curr = ft_timestamp();
	while ((ft_timestamp() - curr) < ms)
		usleep(100);
}
