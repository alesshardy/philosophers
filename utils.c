/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:14:45 by apintus           #+#    #+#             */
/*   Updated: 2024/06/26 12:54:22 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(size_t time)
{
	while (get_time() < time)
		continue ;
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t time, t_table *table)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (dinner_end(table))
			break ;
		usleep(500);
	}
}

// void	ft_usleep(size_t time, t_table *table)
// {
// 	size_t	end;

// 	end = get_time() + time;
// 	while (!dinner_end(table) && get_time() < end)
// 		usleep(500);
// }

void	cleanning(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->dead_mtx);
	pthread_mutex_destroy(&table->count_meal_mtx);
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->last_meal_mtx);
}
