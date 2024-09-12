#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_fork
{
    pthread_mutex_t mu;
    int locked;
} t_fork;

typedef struct s_philo
{
    int				id;
    int             dead;
    int				meals_eaten;
    size_t			start_time;
    size_t          time_since_eaten;
    size_t			time_to_die;
    size_t			time_to_eat;
    size_t			time_to_sleep;
    int				num_of_philos;
    int				num_times_to_eat;
    int             is_alive;
    t_fork          *left_fork;
    t_fork          *right_fork;
}t_philo;

size_t	time_now(void);
void parse_input(int * inp, int argc, char *argv[]);
int ft_atoi(char * a );
void* philo_routine(void * arg);
pthread_t *create_philo(int philo_count, int *inp, t_fork *forks);





#endif