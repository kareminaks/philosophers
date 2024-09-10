#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
#include <pthread.h>


typedef struct s_philo
{
    int				id;
    int				meals_eaten;
    size_t			start_time;
    size_t			time_to_die;
    size_t			time_to_eat;
    size_t			time_to_sleep;
    int				num_of_philos;
    int				num_times_to_eat;
}t_philo;

void parse_input(int * inp, int argc, char *argv[]);
int ft_atoi(char * a );
void* philo_routine(void * arg);
void create_philo(int philo_count, int *inp);




#endif