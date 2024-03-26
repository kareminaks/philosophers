#include "philo.h"

void parse_input(int * inp, int argc, char *argv[])
{
    int n = 0;
    if ((argc != 5) && (argc! =6))
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
{(void)arg;
    printf("new philo has joined the table\n");
    return NULL;
}

void create_philo(int philo_count)
{
    pthread_t *threads = malloc(philo_count * sizeof(pthread_t));
    int i = 0;
    while(i < philo_count)
    {
    if (pthread_create(&threads[i], NULL, philo_routine, NULL) != 0) {
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
    create_philo(philo_count);
    return (0);
}

