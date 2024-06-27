/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:14:15 by apintus           #+#    #+#             */
/*   Updated: 2024/06/25 14:59:51 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (ft_putstr_fd("Only allow positive value\n", 2), NULL);
	if (!is_digit(*str))
		return (ft_putstr_fd("Input not a correct digit\n", 2), NULL);
	nbr = str;
	while (is_digit(*str++))
		++len;
	--str;
	if (*str != '\0')
		return (ft_putstr_fd("Input not a correct digit\n", 2), NULL);
	if (len > 10)
		return (ft_putstr_fd("Value too big, INT_MAX is the limit\n", 2), NULL);
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
		return (ft_putstr_fd("Value too big, INT_MAX is the limit\n", 2), -1);
	return (nbr);
}

int	parse_arg(char **av, t_table *table)
{
	table->philo_nbr = ft_atol(av[1]);
	if (table->philo_nbr == -1)
		return (1);
	table->time_to_die = ft_atol(av[2]);
	if (table->time_to_die == -1)
		return (1);
	table->time_to_eat = ft_atol(av[3]);
	if (table->time_to_eat == -1)
		return (1);
	table->time_to_sleep = ft_atol(av[4]);
	if (table->time_to_sleep == -1)
		return (1);
	return (0);
}

int	parser(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	if (parse_arg(av, table))
		return (1);
	if (ac == 6)
	{
		table->meal_nbr = ft_atol(av[5]);
		if (table->meal_nbr == -1)
			return (1);
	}
	else
		table->meal_nbr = 0;
	if (table->philo_nbr < 1 || table->time_to_die < 60
		|| table->time_to_eat < 60 || table->time_to_sleep < 60
		|| (ac == 6 && table->meal_nbr < 1))
	{
		ft_putstr_fd("Error: Wrong argument\n", 2);
		return (1);
	}
	return (0);
}
