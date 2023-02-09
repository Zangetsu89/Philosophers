/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:16:47 by edawood           #+#    #+#             */
/*   Updated: 2023/01/15 20:33:43 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	init_mutex(t_philos *philos)
{
	if (pthread_mutex_init(&philos->dead, NULL) != SUCCESS)
		return (false);
	if (pthread_mutex_init(&philos->time, NULL) != SUCCESS)
	{
		pthread_mutex_destroy(&philos->dead);
		return (false);
	}
	if (pthread_mutex_init(&philos->creation, NULL) != SUCCESS)
	{
		pthread_mutex_destroy(&philos->dead);
		pthread_mutex_destroy(&philos->time);
		return (false);
	}
	return (true);
}

bool	init_data(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->number_of_philosophers)
	{
		if (pthread_mutex_init(&philos->mutex[i], NULL) != SUCCESS)
			return (false);
		if (pthread_mutex_init(&philos->philo_data[i].eat_count_mutex, NULL) \
		!= SUCCESS)
			return (false);
		philos->philo_data[i].id = i;
		philos->philo_data[i].eat = get_time();
		philos->philo_data[i].philos = philos;
		philos->philo_data[i].left_fork = i;
		philos->philo_data[i].right_fork = (i + 1) % \
		philos->number_of_philosophers;
		if (philos->num_must_eat != DEF_MUST_EAT)
			philos->philo_data[i].eat_count = philos->num_must_eat;
		else
			philos->philo_data[i].eat_count = DEF_MUST_EAT;
		i++;
	}
	return (true);
}

bool	init_philo(t_philos *philos)
{
	if (philos->number_of_philosophers < MIN_PHILOS || \
		philos->number_of_philosophers > MAX_PHILOS)
	{
		philos->wrong_num_of_philos = true;
		return (false);
	}
	philos->mutex = malloc(sizeof(pthread_mutex_t) * \
	philos->number_of_philosophers);
	if (!philos->mutex)
		return (false);
	philos->philo_data = malloc(sizeof(t_philo_data) * \
	philos->number_of_philosophers);
	if (!philos->philo_data)
		return (false);
	return (true);
}

bool	ft_init(int argc, char **argv, t_philos *philos)
{
	philos->number_of_philosophers = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos->num_must_eat = ft_atoi(argv[5]);
	else
		philos->num_must_eat = DEF_MUST_EAT;
	if (!init_philo(philos))
		return (false);
	if (!init_mutex(philos))
		return (false);
	if (!init_data(philos))
	{
		ft_destroy(philos);
		return (false);
	}
	if (philos->num_must_eat < DEF_MUST_EAT || philos->time_to_die <= ERROR || \
		philos->number_of_philosophers > MAX_PHILOS || \
		philos->time_to_eat <= ERROR || philos->time_to_sleep <= ERROR || \
		philos->num_must_eat == ERROR)
		return (false);
	return (true);
}
