/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:36 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/09/13 15:16:37 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_2_forks(t_philo *philo, size_t max_ms)
{
	size_t	start;
	size_t	end;
	t_fork	*left;
	t_fork	*right;

	start = time_now();
	end = start + max_ms;
	left = philo->left_fork;
	right = philo->right_fork;
	while (time_now() < end)
	{
		pthread_mutex_lock(&left->mu);
		pthread_mutex_lock(&right->mu);
		if (left->locked == 0 && right->locked == 0)
		{
			left->locked = 1;
			report(philo, "has taken a fork");
			right->locked = 1;
			report(philo, "has taken a fork");
			pthread_mutex_unlock(&left->mu);
			pthread_mutex_unlock(&right->mu);
			return (1);
		}
		pthread_mutex_unlock(&left->mu);
		pthread_mutex_unlock(&right->mu);
		usleep(1000);
	}
	return (0);
}

void	unlock_fork(t_fork *mu)
{
	pthread_mutex_lock(&mu->mu);
	mu->locked = 0;
	pthread_mutex_unlock(&mu->mu);
}

void	destroy_forks(int philo_count, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_mutex_destroy(&forks[i].mu) != 0)
		{
			printf("error destroying\n");
		}
		i++;
	}
	free(forks);
}
