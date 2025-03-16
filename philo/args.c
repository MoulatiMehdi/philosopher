#include "philosopher.h"

bool	ft_args_isvalid(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage : ./philo nbr_philos time_die time_eat time_sleep ");
		printf("[nbr_meals_per_philo]\n");
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error : %s invalid number\n", argv[i]);
			return (false);
		}
		if (i == 1 && ft_atoi(argv[i]) > PHILO_MAX)
		{
			printf("Error : %s exceed theads maximum (PHILO_MAX = %d)\n",
				argv[i], PHILO_MAX);
			return (false);
		}
		i++;
	}
	return (true);
}
