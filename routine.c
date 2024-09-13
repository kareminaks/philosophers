/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:44:20 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/09/13 15:19:12 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	size_t	time_to_live;

	report(philo, "is thinking");
	time_to_live = philo->time_to_die - philo->time_to_sleep;
	if (lock_2_forks(philo, time_to_live))
	{
		return ;
	}
	philo->dead = 1;
	die(philo);
}

void	eating(t_philo *philo)
{
	report(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	philo->meals_eaten++;
	philo->time_since_eaten = 0;
	unlock_fork(philo->left_fork);
	unlock_fork(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	report(philo, "is sleeping");
	if (philo->time_to_die <= philo->time_to_sleep)
	{
		usleep((philo->time_to_sleep - philo->time_to_die) * 1000);
		philo->dead = 1;
		die(philo);
		return ;
	}
	usleep((philo->time_to_sleep) * 1000);
	philo->time_since_eaten = philo->time_to_sleep;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		thinking(philo);
		if (did_someone_die(philo))
			return (NULL);
		eating(philo);
		if ((philo->num_times_to_eat != NO_VALUE)
			&& (philo->meals_eaten >= philo->num_times_to_eat))
		{
			report(philo, "is thinking");
			return (NULL);
		}
		if (did_someone_die(philo))
			return (NULL);
		sleeping(philo);
		if (did_someone_die(philo))
			return (NULL);
	}
	return (NULL);
}