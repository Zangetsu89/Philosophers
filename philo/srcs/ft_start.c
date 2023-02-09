/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:41:07 by edawood           #+#    #+#             */
/*   Updated: 2023/01/15 20:26:07 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	thread_creation_check(t_philo_data *philo_data)
{
	int	created_threads;

	pthread_mutex_lock(&philo_data->philos->creation);
	created_threads = philo_data->philos->created_threads;
	pthread_mutex_unlock(&philo_data->philos->creation);
	if (created_threads != philo_data->philos->number_of_philosophers)
		return (false);
	return (true);
}

static bool	ft_create(t_philos *philos)
{
	int	i;

	pthread_mutex_lock(&philos->creation);
	i = 0;
	philos->philos_count_after_create = 0;
	philos->created_threads = 0;
	philos->is_dead = false;
	while (i < philos->number_of_philosophers)
	{
		pthread_mutex_lock(&philos->time);
		philos->philo_data[i].last_eat = get_time();
		pthread_mutex_unlock(&philos->time);
		if (pthread_create(&philos->thread[i], NULL, \
		ft_routine, &philos->philo_data[i]) != SUCCESS)
			break ;
		philos->philos_count_after_create++;
		i++;
		philos->created_threads = i;
	}
	philos->start_time = get_time();
	pthread_mutex_unlock(&philos->creation);
	if (philos->philos_count_after_create != philos->number_of_philosophers)
		return (false);
	return (true);
}

static void	ft_join(t_philos *philos)
{
	int	i;

	i = philos->philos_count_after_create;
	while (i >= 0)
	{
		pthread_join(philos->thread[i], NULL);
		i--;
	}
}

void	ft_destroy(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->number_of_philosophers)
	{
		pthread_mutex_destroy(&philos->mutex[i]);
		pthread_mutex_destroy(&philos->philo_data[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&philos->time);
	pthread_mutex_destroy(&philos->dead);
	pthread_mutex_destroy(&philos->creation);
}

bool	ft_start(t_philos *philos)
{
	if (!ft_create(philos))
	{
		printf("Error: Thread creation failed\n");
		ft_destroy(philos);
		return (false);
	}
	ft_check_dead(philos);
	ft_join(philos);
	ft_destroy(philos);
	return (true);
}
