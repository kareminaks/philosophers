#include "philo.h"

char * parse_input(int * inp, int argc, char *argv[])
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
        return 0;
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
    int i=0;
    parse_input(inp,argc-1,&argv[1]);
   while (i<5)
   {printf("%d ",inp[i]);
   i++;
   }
    return (0);
}

