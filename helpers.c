/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:50:33 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/09/13 16:42:13 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report_died(t_philo *philo)
{
	size_t	time;

	time = time_now() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf("%lu %d died\n", time, philo->id + 1);
	pthread_mutex_unlock(philo->write_lock);
}

int	ft_atoi(char *a)
{
	int	res;
	int	sign;
	int	i;

	i = 0;
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
		if ((a[i] >= '0') && (a[i] <= '9'))
		{
			res = res * 10 + a[i] - '0';
			i++;
		}
		else
			exit(0);
	}
	return (res * sign);
}

size_t	time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	parse_input(int *inp, int argc, char *argv[])
{
	int	n;

	n = 0;
	inp[4] = NO_VALUE;
	if ((argc != 4) && (argc != 5))
	{
		printf("Invalid amount of input data, try again\n");
		exit(0);
	}
	else
	{
		while ((n < 5) && argv[n + 1])
		{
			inp[n] = ft_atoi(argv[n + 1]);
			n++;
		}
	}
}

void	check_input(int *inp)
{
	if ((inp[0] < 1) || (inp[0] > 200))
	{
		printf("Insufficient number of philosophers\n");
		exit(0);
	}
	else if (inp[1] < 1)
	{
		printf("Insufficient time to die\n");
		exit(0);
	}
	else if (inp[2] < 1)
	{
		printf("Insufficient time to eat\n");
		exit(0);
	}
	else if (inp[3] < 1)
	{
		printf("Insufficient time to sleep\n");
		exit(0);
	}
	else if ((inp[4] != NO_VALUE) && (inp[4] <= 0))
	{
		printf("Insufficient amount of times to eat\n");
		exit(0);
	}
}
