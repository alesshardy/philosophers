/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:14:45 by apintus           #+#    #+#             */
/*   Updated: 2024/06/21 19:20:52 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(size_t time)
{
	while (get_time() < time)
		continue;
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
		usleep(100);
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

void	cleanning(t_table *table)
{
	size_t	i;

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
