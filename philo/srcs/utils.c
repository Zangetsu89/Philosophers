/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:39:39 by edawood           #+#    #+#             */
/*   Updated: 2023/01/15 12:50:45 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (true);
}

void	ft_free(t_philos *philos)
{
	free(philos->mutex);
	free(philos->philo_data);
}

bool	check_dead(t_philos *philos)
{
	bool	is_dead;

	pthread_mutex_lock(&philos->dead);
	is_dead = philos->is_dead;
	pthread_mutex_unlock(&philos->dead);
	return (is_dead);
}

bool	status(t_philo_data *philo_data, char *str)
{
	size_t	time;
	bool	is_dead;

	pthread_mutex_lock(&philo_data->philos->dead);
	time = get_time() - philo_data->philos->start_time;
	is_dead = philo_data->philos->is_dead;
	if (is_dead == false)
		printf("%ld %d %s\n", time, philo_data->id + 1, str);
	pthread_mutex_unlock(&philo_data->philos->dead);
	return (is_dead);
}
