/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:00:05 by apintus           #+#    #+#             */
/*   Updated: 2024/06/14 19:24:59 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_table(t_table *table)
{
    int i;
    t_philo *philo;

    printf("Table configuration:\n");

    for (i = 0; i < table->philo_nbr; i++)
    {
        philo = table->philos + i;
        printf("Philosopher %d: ", philo->id);
        printf("Left fork: %d, Right fork: %d\n", philo->left_forks->id, philo->right_forks->id);
    }
}

/* static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (i == 0)
	{
		philo->left_forks = forks + philo_nbr - 1;
		philo->right_forks = forks;
	}
	else
	{
		philo->left_forks = forks + i - 1;
		philo->right_forks = forks + i;
	}
} */

static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->left_forks = &forks[(i + 1) % philo_nbr];
	philo->right_forks = &forks[i];
	if (philo->id % 2 == 0)
	{
		philo->left_forks = &forks[i];
		philo->right_forks = &forks[(i + 1) % philo_nbr];
	}

}

static void	philo_init(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->table = table;
		pthread_mutex_init(&philo->philo_mtx, NULL);
		assign_forks(philo, table->forks, i);
	}
}

int	ft_init(t_table *table)
{
	int		i;

	i = -1;
	table->dinner_finished = false;
	table->thread_ready = false;
	table->thread_running = 0;
	pthread_mutex_init(&table->table_mtx, NULL);
	pthread_mutex_init(&table->print_mtx, NULL);
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (printf("Malloc failed\n"), 1);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
		return (printf("Malloc failed\n"), 1);
	while (++i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork_mtx, NULL);
		table->forks[i].id = i;
	}
	philo_init(table);

	print_table(table); // VISUALIZE TABLE
	return (0);
}
