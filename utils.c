/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:14:45 by apintus           #+#    #+#             */
/*   Updated: 2024/07/01 12:15:28 by apintus          ###   ########.fr       */
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
	t_data_time	data;

	data.start = get_time();
	data.remaining = time;
	while (data.remaining > 0)
	{
		if (dinner_end(table))
			break ;
		data.now = get_time();
		if (data.start + time > data.now)
			data.remaining = data.start + time - data.now;
		else
			data.remaining = 0;
		if (data.remaining > 500)
			data.sleep_time = 500;
		else
			data.sleep_time = data.remaining;
		usleep(data.sleep_time);
		data.now = get_time();
		if (data.start + time > data.now)
			data.remaining = data.start + time - data.now;
		else
			data.remaining = 0;
	}
}

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
