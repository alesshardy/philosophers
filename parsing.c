/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:14:15 by apintus           #+#    #+#             */
/*   Updated: 2024/06/21 19:16:27 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				ft_putstr_fd("Error: Wrong argument\n", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parser(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	if (check_args(ac,av))
		return (1);
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->meal_nbr = ft_atoi(av[5]);
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
