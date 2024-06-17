/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:12:13 by apintus           #+#    #+#             */
/*   Updated: 2024/06/17 16:36:51 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static bool	philo_died(t_philo *philo)
{
	long	gap;
	bool	full;

	pthread_mutex_lock(&philo->philo_mtx);
	full = philo->full;
	pthread_mutex_unlock(&philo->philo_mtx);
	if (full)
		return (false);

	pthread_mutex_lock(&philo->philo_mtx);
	gap = get_time(MILLISECOND) - philo->t_last_meal;
	pthread_mutex_unlock(&philo->philo_mtx);
	gap = gap * 1000; // convert to microsecond
	if (gap > philo->table->t_to_die)
		return (true);
	return (false);
}

bool	all_thread_running(t_table *table)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&table->table_mtx);
	if (table->thread_running == table->philo_nbr)
		ret = true;
	pthread_mutex_unlock(&table->table_mtx);
	return (ret);
}

void	*monitor(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_thread_running(table))
		;
	while(!dinner_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !dinner_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				pthread_mutex_lock(&table->table_mtx);
				table->dinner_finished = true;
				print_msg(table->philos + i, DIED);
				pthread_mutex_unlock(&table->table_mtx);
			}
		}
	}
	return (NULL);
}
