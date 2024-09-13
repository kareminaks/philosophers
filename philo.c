/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:52:12 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/09/13 16:13:53 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_someone_died(t_philo *philo)
{
	t_fork	*dead;

	dead = philo->someone_died;
	pthread_mutex_lock(&dead->mu);
	int was_locked = dead->locked;
	dead->locked = 1;
	pthread_mutex_unlock(&dead->mu);
	return !was_locked;
}

int	did_someone_die(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->someone_died->mu);
	dead = philo->someone_died->locked;
	pthread_mutex_unlock(&philo->someone_died->mu);
	return (dead);
}

void	die(t_philo *philo)
{
	if(set_someone_died(philo))
		report_died(philo);
}

void	join_threads(int philo_count, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("error joining\n");
		}
		i++;
	}
	free(threads);
}

int	main(int argc, char *argv[])
{
	int				inp[5];
	t_fork			*forks;
	t_fork			*philo_died;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_t		*threads;

	parse_input(inp, argc - 1, argv);
	check_input(inp);
	forks = create_forks(inp[0]);
	philo_died = create_forks(1);
	pthread_mutex_init(&write_lock, NULL);
	philos = init_philos(inp, forks, philo_died, &write_lock);
	threads = create_threads(inp[0], philos);
	join_threads(inp[0], threads);
	free(philos);
	pthread_mutex_destroy(&write_lock);
	destroy_forks(inp[0], forks);
	destroy_forks(1, philo_died);
	return (0);
}
