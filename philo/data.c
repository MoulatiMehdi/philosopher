#include "philo.h"

long	ft_atoi(const char *str)
{
	unsigned long	res;
	int				i;
	int				c;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			return (-1);
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		c = str[i] - '0';
		res = 10 * res + c;
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

int ft_data_isvalid(t_data  * data)
{
    if(data->meal_min < 0)
        return 0;
    if(data->time_die <= 0)
        return 0;
    if(data->time_sleep <= 0)
        return 0;
    if(data->time_eat <= 0)
        return 0;
    if(data->size <= 0 || data->size > PHILO_MAX)
        return 0;
    return 1;
}

int ft_data_init(t_data * data,int argc,char ** argv)
{
    if(argc < 5 || argc > 6)
        return 1;
    data->size = ft_atoi(argv[1]);
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    data->meal_min = 0;
    if(argc == 6)
        data->meal_min = ft_atoi(argv[5]);
    if(!ft_data_isvalid(data))
        return 1;
    if(argc != 6)
        data->meal_min = -1;
    return 0;
}
