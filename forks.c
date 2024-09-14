/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:36 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/09/14 15:43:52 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_until(size_t until_ms)
{
	size_t	now;

	now = time_now();
	if (until_ms < now)
		return ;
	usleep((until_ms - now) * 1000);
}

int	kek(size_t u)
{
	sleep_until(u);
	return (0);
}

int	lock_2_forks(t_philo *philo, size_t max_ms)
{
	size_t	end;

	usleep(500);
	end = time_now() + max_ms;
	if (philo->left_fork == philo->right_fork)
		return (kek(end));
	while (time_now() < end)
	{
		usleep(100);
		pthread_mutex_lock(&philo->left_fork->mu);
		pthread_mutex_lock(&philo->right_fork->mu);
		if (philo->left_fork->locked == 0 && philo->right_fork->locked == 0)
		{
			philo->left_fork->locked = 1;
			philo->right_fork->locked = 1;
			pthread_mutex_unlock(&philo->left_fork->mu);
			pthread_mutex_unlock(&philo->right_fork->mu);
			report(philo, "has taken a fork");
			report(philo, "has taken a fork");
			return (1);
		}
		pthread_mutex_unlock(&philo->left_fork->mu);
		pthread_mutex_unlock(&philo->right_fork->mu);
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
