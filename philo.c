#include "philo.h"

#define NO_VALUE -1

void parse_input(int * inp, int argc, char *argv[])
{
    int n = 0;
    inp[4] = NO_VALUE;

    if ((argc != 5) && (argc !=6))
        {printf ("Invalid amount of input data, try again\n");
        exit(0);}
    else
    { while ((n < 5) && argv[n])
        {
            inp[n]= ft_atoi(argv[n+1]);
            n++;
        }}
}

void check_input(int * inp)
{
    if ((inp[0] < 1) || (inp[0]>200))
        {printf("Insufficient number of philosophers\n");
        exit(0);}
    else if(inp[1]< 1 )
        {printf("Insufficient time to die\n");
        exit(0);}
    else if(inp[2] < 1 )
        {printf("Insufficient time to eat\n");
        exit(0);}
    else if(inp[3] < 1 )
       {printf("Insufficient time to sleep\n");
        exit(0);}
    else if ((inp[4]) && (inp[4] < 0))
        {printf("Insufficient amount of times to eat\n");
        exit(0);}

}
void* philo_routine(void * arg)
{
    t_philo *philo = arg;


    printf("ruunning philo: id=%d tte=%d ttd=%d tts=%d\n", 
        philo->id, (int)(philo->time_to_eat),(int)(philo->time_to_die), (int)(philo->time_to_sleep));
    return NULL;
}

size_t time_now() {
    return 0;
}

t_philo * fill_philo(int id,int * inp)
{
    t_philo *philo = malloc(sizeof(t_philo));
    philo->id = id;
    philo->meals_eaten = 0;
    philo->start_time = time_now();
    philo->time_to_die = inp[1];
    philo->time_to_eat = inp[2];
    philo->time_to_sleep = inp[3];
    philo->num_of_philos = inp[0];
    philo->num_times_to_eat = inp[4];

    return(philo);
}



void create_philo(int philo_count, int *inp)
{
    pthread_t *threads = malloc(philo_count * sizeof(pthread_t));
    int i = 0;
    t_philo * philo;
    while(i < philo_count)
    {   
        philo = fill_philo(i, inp); // TODO free philo later
        if (pthread_create(&threads[i], NULL, philo_routine, philo) != 0) {
            printf("Failed to create thread\n");
    }
    i++;
    printf("Thread %d has started\n", i);}
    for (i = 0; i < philo_count; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("error joining\n");
        }
        printf("Thread %d has finished execution\n", i);
    }
    free(threads);
}

int ft_atoi(char * a )
{
    int	res;
	int	sign;
    int i =0;

	res = 0;
	sign = 1;
	while (a[i] == 32 || (a[i] >= 9 && a[i] <= 13))
		i++;
	if (a[i] == '-')
		sign *= -1;
	if (a[i] == '-' || a[i] == '+')
		i++;
	 while (a[i])
    { 
    if ((a[i]>= '0') && ( a[i] <= '9'))
        {res = res*10+ a[i]-'0';
        i++;}
    else {
        printf("only numbers in input,please\n");
        exit(0);
    }
    }   
    return(res*sign);
    }

int main(int argc, char *argv[])
{
    int inp[5];
    parse_input(inp,argc-1,argv);
    int philo_count= inp[0];
    check_input(inp);
    create_philo(philo_count, inp);
    
    return (0);
}

