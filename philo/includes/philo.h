/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:19:45 by edawood           #+#    #+#             */
/*   Updated: 2023/01/15 20:34:03 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

# define ERROR 0
# define SUCCESS 0
# define ONE_SEC 1000
# define DEF_MUST_EAT -1
# define MAX_PHILOS 200
# define MIN_PHILOS 1

typedef struct s_philo_data
{
	int				id;
	int				eat;
	int				left_fork;
	int				right_fork;
	int				last_eat;
	int				eat_count;
	pthread_mutex_t	eat_count_mutex;
	struct s_philos	*philos;
}			t_philo_data;

typedef struct s_philos
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			is_dead;
	bool			wrong_num_of_philos;
	int				created_threads;
	int				philos_count_after_create;
	int				num_must_eat;
	pthread_t		thread[201];
	size_t			start_time;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	time;
	pthread_mutex_t	dead;
	pthread_mutex_t	creation;
	t_philo_data	*philo_data;
}	t_philos;

bool		ft_init(int argc, char **argv, t_philos *philos);
int			ft_atoi(const char *str);

bool		thread_creation_check(t_philo_data *philo_data);
bool		ft_start(t_philos *philos);
void		ft_destroy(t_philos *philos);

bool		ft_eat(t_philo_data *philo_data);
void		*ft_routine(void *value);

void		ft_check_dead(t_philos *philos);

size_t		get_time(void);
long long	time_diff(long long past, long long present);
void		better_sleep(long long time, t_philos *philos);

int			ft_error(char *str);
void		ft_free(t_philos *philos);
bool		check_dead(t_philos *philos);
bool		status(t_philo_data *data, char *str);

#endif