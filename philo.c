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

int lock_2_forks(t_philo *philo, size_t max_ms) {
    size_t start = time_now();
    size_t end = start + max_ms;
    t_fork* left = philo->left_fork;
    t_fork* right = philo->right_fork;

    while(time_now() < end) {
        pthread_mutex_lock(&left->mu);
        pthread_mutex_lock(&right->mu);
        if (left->locked == 0 && right->locked == 0) {
            left->locked = 1;
            right->locked = 1;
            pthread_mutex_unlock(&left->mu);
            pthread_mutex_unlock(&right->mu);
            return 1;
        }
        pthread_mutex_unlock(&left->mu);
        pthread_mutex_unlock(&right->mu);
        usleep(10000);   
    }

    return 0;
}

void unlock_fork(t_fork* mu) {
    pthread_mutex_lock(&mu->mu);
    mu->locked = 0;
    pthread_mutex_unlock(&mu->mu);
}

void report(int id, char* action) {
	printf("%lu %d is %s\n", time_now(), id + 1, action);
}

void thinking(t_philo *philo) {
    report(philo->id, "thinking");
    size_t time_to_live = philo->time_to_die - philo->time_to_sleep;
    if (lock_2_forks(philo, time_to_live)) {
        return;
    }
    philo->dead = 1;
}

void eating (t_philo *philo)
{
    report(philo->id, "eating");
    usleep(philo->time_to_eat*1000);
    philo->meals_eaten++;
    philo->time_since_eaten = 0;
    unlock_fork(philo->left_fork);
    unlock_fork(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
    report(philo->id, "sleeping");
    if (philo->time_to_die<= philo->time_to_sleep)
        {
            usleep((philo->time_to_sleep - philo->time_to_die)*1000);
            philo->dead = 1;
            return;
        }
	usleep((philo->time_to_sleep)*1000);
    philo->time_since_eaten = philo->time_to_sleep;
}
void* philo_routine(void * arg)
{   

    t_philo *philo = arg;

    printf("ruunning philo: id=%d tte=%d ttd=%d tts=%d\n", 
        philo->id, (int)(philo->time_to_eat),(int)(philo->time_to_die), (int)(philo->time_to_sleep));

    while ((philo->dead!=1)&&(philo->num_times_to_eat>philo->meals_eaten))
    {
        thinking(philo);
        eating(philo);
        sleeping(philo);
    }
    return NULL;
}


t_philo * fill_philo(int id,int * inp, t_fork *forks)
{
    t_philo *philo = malloc(sizeof(t_philo));
    int n = inp[0];
    philo->id = id;
    philo->dead = 0;
    philo->meals_eaten = 0;
    philo->start_time = time_now();
    philo->time_since_eaten = time_now();
    philo->time_to_die = inp[1];
    philo->time_to_eat = inp[2];
    philo->time_to_sleep = inp[3];
    philo->num_of_philos = n;
    philo->num_times_to_eat = inp[4];
    philo->is_alive = 1;
    philo->right_fork = &forks[id];
    if (id == 0)
        philo->left_fork = &forks[n-1];
    else 
        philo->left_fork = &forks[id-1];
    return(philo);
}

t_fork *create_forks(int philo_count)
{   int i = 0;
    t_fork *forks = malloc(philo_count*sizeof(t_fork));
    while(i < philo_count)
    {
        forks[i].locked = 0;
        pthread_mutex_init(&forks[i].mu, NULL);
        i++;
    }
    return(forks);


}

void create_philo(int philo_count, int *inp, t_fork *forks)
{
    pthread_t *threads = malloc(philo_count * sizeof(pthread_t));
    int i = 0;
    t_philo * philo;
    while(i < philo_count)
    {   
        philo = fill_philo(i, inp, forks); // TODO free philo later
        if (pthread_create(&threads[i], NULL, philo_routine, philo) != 0) {
            printf("Failed to create thread\n");
            exit(1);
        }
        printf("Thread %d has started\n", i);
        i++;
    }
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


size_t	time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(int argc, char *argv[])
{
    int inp[5];
    parse_input(inp,argc-1,argv);
    int philo_count= inp[0];
    check_input(inp);
    t_fork* forks =create_forks(philo_count);
    create_philo(philo_count, inp, forks);
    
    return (0);
}

