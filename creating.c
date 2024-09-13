/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:41:53 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/09/13 15:17:04 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(int *inp, t_fork *forks, t_fork *philo_died,
		pthread_mutex_t *write_lock)
{
	t_philo	*philos;
	int		i;

	philos = malloc(inp[0] * sizeof(t_philo));
	i = 0;
	while (i < inp[0])
	{
		fill_philo(&philos[i], i, inp, forks, philo_died, write_lock);
		i++;
	}
	return (philos);
}

pthread_t	*create_threads(int philo_count, t_philo *philos)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(philo_count * sizeof(pthread_t));
	i = 0;
	while (i < philo_count)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
		{
			printf("Failed to create thread\n");
			exit(1);
		}
		i++;
	}
	return (threads);
}

t_fork	*create_forks(int philo_count)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(philo_count * sizeof(t_fork));
	while (i < philo_count)
	{
		forks[i].locked = 0;
		pthread_mutex_init(&forks[i].mu, NULL);
		i++;
	}
	return (forks);
}

void	fill_philo(t_philo *philo, int id, int *inp, t_fork *forks,
		t_fork *philo_died, pthread_mutex_t *write_lock)
{
	int	n;

	n = inp[0];
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
	philo->someone_died = philo_died;
	philo->write_lock = write_lock;
	philo->right_fork = &forks[id];
	if (id == 0)
		philo->left_fork = &forks[n - 1];
	else
		philo->left_fork = &forks[id - 1];
}
