/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:38:00 by apintus           #+#    #+#             */
/*   Updated: 2024/06/24 13:52:27 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->dead_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&table->count_meal_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&table->print_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&table->last_meal_mtx, NULL))
		return (1);
	return (0);
}

static void	philo_forks_init(t_philo *philo, int i)
{
	if (philo->position % 2)
	{
		philo->left_fork = &philo->table->forks[i];
		philo->right_fork = &philo->table->forks[(i + 1)
			% philo->table->philo_nbr];
	}
	else
	{
		philo->right_fork = &philo->table->forks[i];
		philo->left_fork = &philo->table->forks[(i + 1)
			% philo->table->philo_nbr];
	}
}

static int	init_forks(t_table *table)
{
	long	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	if (!table->forks)
	{
		free(table->philos);
		return (1);
	}
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			free(table->philos);
			free(table->forks);
			return (1);
		}
		philo_forks_init(&table->philos[i], i);
		i++;
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	long	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (1);
	memset(table->philos, 0, sizeof(t_philo) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].position = i + 1;
		table->philos[i].table = table;
		table->philos[i].count_meal = 0;
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	if (init_philos(table) || init_forks(table))
		return (1);
	table->dead = 0;
	return (0);
}
