#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
#include <pthread.h>

typedef struct s_philo
{


}t_philo;


void parse_input(int * inp, int argc, char *argv[]);
int ft_atoi(char * a );
void* philo_routine(void * arg);
void create_philo(int philo_count);




#endif