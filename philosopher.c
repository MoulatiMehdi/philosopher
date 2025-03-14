#include "philosopher.h"

t_philo	*ft_philosopher_new(void)
{
	static int	id = 1;
	t_philo		*philosopher;

	philosopher = malloc(sizeof(t_philo));
	if (philosopher == NULL)
		return (NULL);
	philosopher->id = id;
	philosopher->state = STATE_THINKING;
	philosopher->last_meal = ft_timestamp();
	return (philosopher);
}

t_philo	**ft_philosophers_new(long n)
{
	long	i;
	t_philo	**philosophers;

	philosophers = malloc(sizeof(t_philo *) * (n + 1));
	if (philosophers == NULL)
		return (NULL);
	memset(philosophers, 0, sizeof(t_philo *) * (n + 1));
	i = 0;
	while (i < n)
	{
		philosophers[i] = ft_philosopher_new();
		i++;
	}
	return (philosophers);
}
