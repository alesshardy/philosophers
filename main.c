/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:14:03 by apintus           #+#    #+#             */
/*   Updated: 2024/06/27 15:00:39 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_full(t_table *table)
{
	long	i;

	i = 0;
	if (table->meal_nbr == 0)
		return ;
	while (i < table->philo_nbr)
	{
		if (table->philos[i].count_meal == table->meal_nbr)
			i++;
		else
			break ;
	}
	if (i == table->philo_nbr)
	{
		pthread_mutex_lock(&table->print_mtx);
		printf(M"All philo are full\n"RST);
		pthread_mutex_unlock(&table->print_mtx);
	}
}

void	print_msg(t_philo *philo, int msg)
{
	pthread_mutex_lock(&philo->table->print_mtx);
	if (dinner_end(philo->table) && msg != DIED)
	{
		pthread_mutex_unlock(&philo->table->print_mtx);
		return ;
	}
	if (msg == DIED)
	{
		printf("%s%09zu %zu died%s\n", RED,
			get_time() - philo->table->time_start_dinner, philo->id, RST);
		set_death(philo->table);
	}
	else if (msg == EAT)
		printf("%s%09zu %zu is eating%s\n", G,
			get_time() - philo->table->time_start_dinner, philo->id, RST);
	else if (msg == SLEEP)
		printf("%s%09zu %zu is sleeping%s\n", B,
			get_time() - philo->table->time_start_dinner, philo->id, RST);
	else if (msg == THINK)
		printf("%s%09zu %zu is thinking%s\n", Y,
			get_time() - philo->table->time_start_dinner, philo->id, RST);
	else if (msg == FORK)
		printf("%s%09zu %zu has taken a fork%s\n", W,
			get_time() - philo->table->time_start_dinner, philo->id, RST);
	pthread_mutex_unlock(&philo->table->print_mtx);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->last_meal_mtx);
	philo->last_meal = philo->table->time_start_dinner;
	pthread_mutex_unlock(&philo->table->last_meal_mtx);
	wait_all_threads(philo->table->time_start_dinner);
	if (philo->table->philo_nbr == 1)
	{
		ft_usleep(philo->table->time_to_die, philo->table);
		if (!dinner_end(philo->table))
			print_msg(philo, DIED);
		return (NULL);
	}
	if (philo->position % 2)
		ft_usleep(philo->table->time_to_eat, philo->table);
	while (!dinner_end(philo->table))
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

int	dinner(t_table *table)
{
	long	i;

	i = 0;
	table->time_start_dinner = get_time() + (table->philo_nbr * 20);
	while (i < table->philo_nbr)
	{
		table->philos[i].last_meal = table->time_start_dinner;
		if (pthread_create(&table->philos[i].thread, NULL,
				&philo_life, &table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &monitor, table))
		return (1);
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
		i++;
	}
	check_full(table);
	if (pthread_join(table->monitor, NULL))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (parser(ac, av, &table))
		return (1);
	if (init_table(&table))
		return (1);
	if (init_mutex(&table))
		return (1);
	if (dinner(&table))
		return (1);
	cleanning(&table);
	return (0);
}
