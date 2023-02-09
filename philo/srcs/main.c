/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:05:25 by edawood           #+#    #+#             */
/*   Updated: 2023/01/15 20:10:09 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_philos	philos;

	philos.philo_data = NULL;
	if (argc != 5 && argc != 6)
		return (ft_error("Error: Wrong number of arguments"));
	philos.wrong_num_of_philos = false;
	if (!ft_init(argc, argv, &philos))
	{
		if (philos.wrong_num_of_philos == false)
			ft_free(&philos);
		if (philos.wrong_num_of_philos == true)
			return (ft_error("Error: Wrong number of philosophers"));
		return (ft_error("Error: Initialization failed"));
	}
	if (!ft_start(&philos))
		return (ft_error("Error: ft_start failed"));
	ft_free(&philos);
	return (0);
}
