/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:51:10 by apintus           #+#    #+#             */
/*   Updated: 2024/06/17 17:28:37 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static char	*check_input(char *str)
{
	int		len;
	char	*nbr;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (error_handler("Only allow positive value"));
	if (!is_digit(*str))
		return (error_handler("Input not a correct digit"));
	nbr = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		return (error_handler("Value too big, INT_MAX is the limit"));
	return (nbr);
}

static long	ft_atol(char *str)
{
	long	nbr;

	nbr = 0;
	str = check_input(str);
	if (str == NULL)
		return (-1);
	while (is_digit(*str))
		nbr = (nbr * 10) + (*str++ - 48);
	if (nbr > INT_MAX)
		return (printf("Value too big, INT_MAX is the limit\n"), -1);
	return (nbr);
}

//x 1e3 to convert from Milliseconde to Microseconde (need by usleep)
int	parser(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	if (table->philo_nbr == -1)
		return (1);
	table->t_to_die = ft_atol(av[2]) * 1e3;
	if (table->t_to_die == -1000)
		return (1);
	table->t_to_eat = ft_atol(av[3]) * 1e3;
	if (table->t_to_eat == -1000)
		return (1);
	table->t_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->t_to_sleep == -1000)
		return (1);
	if (table->t_to_die < 60e3 || table->t_to_eat < 60e3
		|| table->t_to_sleep < 60e3)
		return (printf("Use timestamp above 60ms\n"), 1);
	if (av[5])
	{
		table->max_meals = ft_atol(av[5]);
		if (table->max_meals == -1)
			return (1);
	}
	else
		table->max_meals = -2; // flag
	return (0);
}
