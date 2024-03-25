#include "philo.h"

void parse_input(int * inp, int argc, char *argv[])
{
    int n = 0;
    if (argc < 5)
    {
        while (n < 4)
        {
            inp[n]= ft_atoi(argv[n]);
            n++;
        }
        inp[4] = 0;
    }
    else 
    { while (n < 5)
        {
            inp[n]= ft_atoi(argv[n]);
            n++;
        }}
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
        printf("Failed to create thread");
    }
    i++;
    printf("Thread %d has started\n", i);}
    for (i = 0; i < philo_count; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("error joining");
        }
        printf("Thread %d has finished execution\n", i);
    }
}

int ft_atoi(char * a )
{
    int i =0;
    int num =0;
    while (a[i])
    { if ((a[i]>= '0') && ( a[i] <= '9'))
    num = num*10+ a[i]-'0';
    i++;
    }
    return(num);
    }

int main(int argc, char *argv[])
{
    int inp[5];
    parse_input(inp,argc-1,&argv[1]);
    int philo_count= inp[0];
    create_philo(philo_count);
    return (0);
}

