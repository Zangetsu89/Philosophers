/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:08:11 by edawood           #+#    #+#             */
/*   Updated: 2023/01/15 20:19:14 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_dead(t_philos *philos, int i)
{
	pthread_mutex_lock(&philos->dead);
	philos->is_dead = true;
	printf("%ld %d died\n", \
	get_time() - philos->start_time, philos->philo_data[i].id + 1);
	pthread_mutex_unlock(&philos->dead);
}

int	check_eat_count(t_philos *philos, int i)
{
	pthread_mutex_lock(&philos->philo_data[i].eat_count_mutex);
	if (philos->philo_data[i].eat_count == 0 && \
	philos->philo_data[i].philos->num_must_eat != DEF_MUST_EAT)
	{
		pthread_mutex_unlock(&philos->philo_data[i].eat_count_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->philo_data[i].eat_count_mutex);
	return (0);
}

long	get_current_time(t_philos *philos, int i)
{
	long	current_time;

	pthread_mutex_lock(&philos->time);
	current_time = get_time() - philos->philo_data[i].last_eat;
	pthread_mutex_unlock(&philos->time);
	return (current_time);
}

void	ft_check_dead(t_philos *philos)
{
	int		i;
	long	current_time;
	int		done_eating;

	while (1)
	{
		i = 0;
		done_eating = 0;
		while (i < philos->number_of_philosophers)
		{
			done_eating += check_eat_count(philos, i);
			current_time = get_current_time(philos, i);
			if ((int)current_time > philos->time_to_die)
				return (print_dead(philos, i));
			i++;
		}
		if (done_eating == philos->number_of_philosophers)
		{
			pthread_mutex_lock(&philos->dead);
			philos->is_dead = true;
			pthread_mutex_unlock(&philos->dead);
			return ;
		}
	}
}
