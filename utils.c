/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:06:22 by apintus           #+#    #+#             */
/*   Updated: 2024/06/17 18:58:02 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_code code)
{
	struct timeval	time;

	if(gettimeofday(&time, NULL))
		return (printf("gettimeofday failed"), -1);
	if (code == SECOND)
		return (time.tv_sec);
	else if (code == MILLISECOND)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	else if (code == MICROSECOND)
		return (time.tv_sec * 1000000 + time.tv_usec);
	return (-1);
}

void	my_usleep(long time, t_table *table)
{
	long	start;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < time)
	{
		if (dinner_finished(table))
			break ;
		usleep(100);
	}
}

void	wait_all_thread(t_table *table)
{
	bool	ready;

	ready = false;
	while (!ready)
	{
		pthread_mutex_lock(&table->table_mtx);
		ready = table->thread_ready;
		pthread_mutex_unlock(&table->table_mtx);
	}
}

bool	dinner_finished(t_table *table)
{
	bool	finished;

	pthread_mutex_lock(&table->table_mtx);
	finished = table->dinner_finished;
	pthread_mutex_unlock(&table->table_mtx);
	return (finished);
}

void	clean(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&table->philos[i].philo_mtx);
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->print_mtx);
	free(table->philos);
	free(table->forks);
}
