/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:52:12 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/09/13 16:20:00 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_someone_died(t_philo *philo)
{
	t_fork	*dead;
	int		was_locked;

	dead = philo->someone_died;
	pthread_mutex_lock(&dead->mu);
	was_locked = dead->locked;
	dead->locked = 1;
	pthread_mutex_unlock(&dead->mu);
	return (!was_locked);
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
	if (set_someone_died(philo))
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
	t_program_state	g;

	parse_input(g.inp, argc - 1, argv);
	check_input(g.inp);
	g.forks = create_forks(g.inp[0]);
	g.philo_died = create_forks(1);
	pthread_mutex_init(&g.write_lock, NULL);
	g.philos = init_philos(g.inp, g.forks, g.philo_died, &g.write_lock);
	g.threads = create_threads(g.inp[0], g.philos);
	join_threads(g.inp[0], g.threads);
	free(g.philos);
	pthread_mutex_destroy(&g.write_lock);
	destroy_forks(g.inp[0], g.forks);
	destroy_forks(1, g.philo_died);
	return (0);
}
