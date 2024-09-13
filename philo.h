/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:15:08 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/09/13 16:14:31 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef NO_VALUE
#  define NO_VALUE -1
# endif

typedef struct s_fork
{
	pthread_mutex_t	mu;
	int				locked;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				meals_eaten;
	size_t			start_time;
	size_t			time_since_eaten;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_philos;
	int				num_times_to_eat;
	int				is_alive;
	t_fork			*someone_died;
	pthread_mutex_t	*write_lock;
	t_fork			*left_fork;
	t_fork			*right_fork;
}					t_philo;

size_t				time_now(void);

int					ft_atoi(char *a);
int					lock_2_forks(t_philo *philo, size_t max_ms);
int					did_someone_die(t_philo *philo);

void				die(t_philo *philo);
void				join_threads(int philo_count, pthread_t *threads);
void				unlock_fork(t_fork *mu);
void				destroy_forks(int philo_count, t_fork *forks);
void				thinking(t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				*philo_routine(void *arg);
void				parse_input(int *inp, int argc, char *argv[]);
void				check_input(int *inp);
void				report(t_philo *philo, char *action);
void				report_died(t_philo *philo);
void				fill_philo(t_philo *philo, int id, int *inp, t_fork *forks,
						t_fork *philo_died, pthread_mutex_t *write_lock);
int				    set_someone_died(t_philo *philo);
void				*philo_routine(void *arg);

t_philo				*init_philos(int *inp, t_fork *forks, t_fork *philo_died,
						pthread_mutex_t *write_lock);
t_fork				*create_forks(int philo_count);
pthread_t			*create_threads(int philo_count, t_philo *philos);

#endif