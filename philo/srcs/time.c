/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:41:26 by edawood           #+#    #+#             */
/*   Updated: 2023/01/12 17:04:45 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_time(void)
{
	size_t			time;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		return (0);
	time = (current_time.tv_sec * ONE_SEC) + (current_time.tv_usec / ONE_SEC);
	return (time);
}

long long	time_diff(long long past, long long present)
{
	return (present - past);
}

void	better_sleep(long long time, t_philos *philos)
{
	long long	i;

	i = get_time();
	while (!check_dead(philos))
	{
		if (time_diff(i, get_time()) >= time)
			break ;
		usleep(50);
	}
}
