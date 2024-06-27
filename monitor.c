/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:07:38 by apintus           #+#    #+#             */
/*   Updated: 2024/06/27 15:00:19 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dinner_end(t_table *table)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->dead_mtx);
	if (table->dead)
		ret = 1;
	pthread_mutex_unlock(&table->dead_mtx);
	return (ret);
}

void	set_death(t_table *table)
{
	pthread_mutex_lock(&table->dead_mtx);
	table->dead = 1;
	pthread_mutex_unlock(&table->dead_mtx);
}

int	check_death(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->last_meal_mtx);
	time = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->table->last_meal_mtx);
	if (time >= philo->table->time_to_die)
	{
		set_death(philo->table);
		usleep(1000);
		print_msg(philo, DIED);
		return (1);
	}
	return (0);
}

int	handle_end(t_table *table)
{
	long	i;
	int		ret;

	ret = 1;
	i = 0;
	while (i < table->philo_nbr)
	{
		if (check_death(&table->philos[i]))
			return (1);
		if (table->meal_nbr)
		{
			pthread_mutex_lock(&table->count_meal_mtx);
			if (table->philos[i].count_meal < table->meal_nbr)
				ret = 0;
			pthread_mutex_unlock(&table->count_meal_mtx);
		}
		i++;
	}
	if (table->meal_nbr && ret)
	{
		set_death(table);
		return (1);
	}
	else
		return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	wait_all_threads(table->time_start_dinner);
	while (!dinner_end(table))
	{
		if (handle_end(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
