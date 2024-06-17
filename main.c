/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:03:56 by apintus           #+#    #+#             */
/*   Updated: 2024/06/17 18:08:20 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, t_msg msg)
{
	long	gap;

	gap = get_time(MILLISECOND) - philo->table->start_dinner;
	if (msg == FORK && !dinner_finished(philo->table))
		printf(W"%ld	%d has taken a fork\n"RST, gap, philo->id);
	else if (msg == EAT && !dinner_finished(philo->table))
		printf(G"%ld	%d is eating\n"RST, gap, philo->id);
	else if (msg == SLEEP && !dinner_finished(philo->table))
		printf(B"%ld	%d is sleeping\n"RST, gap, philo->id);
	else if (msg == THINK && !dinner_finished(philo->table))
		printf(Y"%ld	%d is thinking\n"RST, gap, philo->id);
	else if (msg == DIED)
		printf(RED"%ld	%d died\n"RST, gap, philo->id);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		//1) parsing
		if(parser(&table, av) == 1)
			return (printf("Parsing Error\n"), 1);
		printf("OK PARSING\n");
		//2) Init
		ft_init(&table);
		//3) Dinner
		dinner(&table);
		//4) Cleanning
		clean(&table);
	}
	else
		return (printf("Wrong Input\nExpect like: ./philo 5 800 200 200 [5]\n"), 1);
}

