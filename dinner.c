/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:21:49 by apintus           #+#    #+#             */
/*   Updated: 2024/06/17 19:01:30 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	long	t_to_think;

	print_msg(philo, THINK);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_to_think = 100;
	my_usleep(t_to_think, philo->table);
}

static void	eat(t_philo *philo)
{
	// take forks
	pthread_mutex_lock(&philo->left_forks->fork_mtx);
	print_msg(philo, FORK);
	pthread_mutex_lock(&philo->right_forks->fork_mtx);
	print_msg(philo, FORK);

	// increase meal counter
	pthread_mutex_lock(&philo->philo_mtx);
	philo->t_last_meal = get_time(MILLISECOND);
	pthread_mutex_unlock(&philo->philo_mtx);
	philo->meals++;
	print_msg(philo, EAT);
	my_usleep(philo->table->t_to_eat, philo->table); // eating
	if (philo->meals == philo->table->max_meals && philo->table->max_meals > 0)
	{
		pthread_mutex_lock(&philo->philo_mtx);
		philo->full = true;
		pthread_mutex_unlock(&philo->philo_mtx);
	}
	// release forks
	pthread_mutex_unlock(&philo->left_forks->fork_mtx);
	pthread_mutex_unlock(&philo->right_forks->fork_mtx);
}

// void	*lonely_philo(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	// wait_all_thread(philo->table);
// 	//set time last meal
// 	pthread_mutex_lock(&philo->philo_mtx);
// 	philo->t_last_meal = get_time(MILLISECOND);
// 	pthread_mutex_unlock(&philo->philo_mtx);
// 	// ++thread running
// 	printf("BBBBBBB\n");
// 	pthread_mutex_lock(&philo->table->table_mtx);
// 	philo->table->thread_running++;
// 	pthread_mutex_unlock(&philo->table->table_mtx);
// 	print_msg(philo, FORK);
// 	while(!dinner_finished(philo->table))
// 		usleep(200);
// 	return (NULL);
// }

static void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// wait all thread ready
	wait_all_thread(philo->table);
	// set time last meal
	pthread_mutex_lock(&philo->philo_mtx);
	philo->t_last_meal = get_time(MILLISECOND);
	pthread_mutex_unlock(&philo->philo_mtx);
	// ++thread running
	pthread_mutex_lock(&philo->table->table_mtx);
	philo->table->thread_running++;
	pthread_mutex_unlock(&philo->table->table_mtx);
	// philo life
	while (!dinner_finished(philo->table))
	{
		if (philo->full)
			break ;
		// EAT
		eat(philo);
		// SLEEP
		print_msg(philo, SLEEP);
		my_usleep(philo->table->t_to_sleep, philo->table);
		// THINK
		think(philo);
	}
	return (NULL); // philo is full
}

void	dinner(t_table *table)
{
	int		i;
	bool	all_philo_full;

	i = -1;
	if (table->max_meals == 0)
		return ;
	else if (table->philo_nbr == 1) //handle 1 philo
	{
		table->start_dinner = get_time(MILLISECOND);
		print_msg(table->philos, FORK);
		my_usleep(table->t_to_die, table);
		print_msg(table->philos, DIED);
		return ;
	}
	else
	{
		while (++i < table->philo_nbr)
		{
			pthread_create(&table->philos[i].thread, NULL, philo_life, &table->philos[i]);
			printf("%d THrEAD CREATE\n", i);
		}
	}
	// thread monitor (death checker)
	pthread_create(&table->monitor, NULL, monitor, table);
	// start of dinner time
	table->start_dinner = get_time(MILLISECOND);
	// wait all thread ready
	pthread_mutex_lock(&table->table_mtx);
	table->thread_ready = true;
	pthread_mutex_unlock(&table->table_mtx);
	printf("Table ready\n");
	// join all threads
	i = -1;
	while (++i < table->philo_nbr)
			pthread_join(table->philos[i].thread, NULL);
	// if we arrive here all philo are full
	pthread_mutex_lock(&table->table_mtx);
	table->dinner_finished = true;
	pthread_mutex_unlock(&table->table_mtx);
	// check if all philo are full and print message
	i = -1;
	if (table->max_meals != 0)
	{
		all_philo_full = true;
		while (++i < table->philo_nbr)
		{
			if (!table->philos[i].full)
			{
				all_philo_full = false;
				break ;
			}
		}
		if (all_philo_full)
			printf(M"All philo are full\n"RST);
	}
	// join monitor
	pthread_join(table->monitor, NULL);
}
