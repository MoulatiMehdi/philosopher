#include "philo.h"

int main(int argc, char *argv[])
{
    t_args args;
    t_philo *philo;
    t_fork *forks;

    if(!ft_args_init(&args,argc, argv))
        return EXIT_FAILURE;
    if(!ft_philos_init(&philo,&forks,&args))
        return EXIT_FAILURE;

    ft_free_memory(philo,forks);
    return EXIT_SUCCESS;
}
