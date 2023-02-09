/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:34:04 by edawood           #+#    #+#             */
/*   Updated: 2023/01/15 20:19:41 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	take_fork(t_philo_data *philo_data)
{
	pthread_mutex_lock(&philo_data->philos->mutex[philo_data->right_fork]);
	if (status(philo_data, "has taken a fork"))
	{
		pthread_mutex_unlock(\
		&philo_data->philos->mutex[philo_data->right_fork]);
		return (false);
	}
	pthread_mutex_lock(&philo_data->philos->mutex[philo_data->left_fork]);
	if (status(philo_data, "has taken a fork"))
	{
		pthread_mutex_unlock(\
		&philo_data->philos->mutex[philo_data->left_fork]);
		pthread_mutex_unlock(\
		&philo_data->philos->mutex[philo_data->right_fork]);
		return (false);
	}
	return (true);
}

static void	ft_drop_fork(t_philo_data *philo_data)
{
	pthread_mutex_unlock(&philo_data->philos->mutex[philo_data->left_fork]);
	pthread_mutex_unlock(&philo_data->philos->mutex[philo_data->right_fork]);
}

bool	ft_eat(t_philo_data *philo_data)
{
	if (status(philo_data, "is eating"))
	{
		ft_drop_fork(philo_data);
		return (false);
	}
	pthread_mutex_lock(&philo_data->philos->time);
	philo_data->last_eat = get_time();
	pthread_mutex_unlock(&philo_data->philos->time);
	pthread_mutex_lock(&philo_data->eat_count_mutex);
	if (philo_data->eat_count != 0 && philo_data->eat_count != DEF_MUST_EAT)
		philo_data->eat_count--;
	pthread_mutex_unlock(&philo_data->eat_count_mutex);
	better_sleep(philo_data->philos->time_to_eat, philo_data->philos);
	ft_drop_fork(philo_data);
	return (true);
}

static void	*single_philo(t_philo_data *philo_data)
{
	status(philo_data, "has taken a fork");
	pthread_mutex_lock(&philo_data->philos->mutex[philo_data->left_fork]);
	better_sleep(philo_data->philos->time_to_die, philo_data->philos);
	pthread_mutex_unlock(&philo_data->philos->mutex[philo_data->left_fork]);
	return (NULL);
}

void	*ft_routine(void *value)
{
	t_philo_data	*philo_data;

	philo_data = (t_philo_data *)value;
	if (thread_creation_check(philo_data) == false)
		return (NULL);
	if (philo_data->philos->number_of_philosophers == 1)
		return (single_philo(philo_data));
	if (philo_data->id % 2 == 1)
		better_sleep(50, philo_data->philos);
	while (1)
	{
		if (!take_fork(philo_data))
			break ;
		if (!ft_eat(philo_data))
			break ;
		if (status(philo_data, "is sleeping"))
			break ;
		better_sleep(philo_data->philos->time_to_sleep, philo_data->philos);
		if (status(philo_data, "is thinking"))
			break ;
	}
	return (NULL);
}
