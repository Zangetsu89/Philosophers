/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:17:04 by edawood           #+#    #+#             */
/*   Updated: 2023/01/13 18:36:49 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static int	whitespace_checker(char c)
{
	return (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ');
}

static int	int_converter(const char *str)
{
	int	result;

	if (!ft_isdigit(*str))
		return (ERROR);
	result = (*str - '0') * -1;
	str++;
	while (ft_isdigit(*str))
	{
		result *= 10;
		result -= (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (ERROR);
	return (result);
}

int	ft_atoi(const char *str)
{
	int	min;

	min = -1;
	while (whitespace_checker(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			min = 1;
		str++;
	}
	return (int_converter(str) * min);
}
