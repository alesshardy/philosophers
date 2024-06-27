/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:56:41 by apintus           #+#    #+#             */
/*   Updated: 2024/06/27 15:00:52 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, FORK);
	if (dinner_end(philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_msg(philo, EAT);
	pthread_mutex_lock(&philo->table->last_meal_mtx);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->last_meal_mtx);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (!dinner_end(philo->table))
	{
		pthread_mutex_lock(&philo->table->count_meal_mtx);
		philo->count_meal++;
		pthread_mutex_unlock(&philo->table->count_meal_mtx);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	if (dinner_end(philo->table))
		return ;
	print_msg(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	think(t_philo *philo)
{
	size_t	time_to_think;

	if (dinner_end(philo->table))
		return ;
	print_msg(philo, THINK);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	else if (philo->table->time_to_sleep > philo->table->time_to_eat)
		return ;
	else
		time_to_think = 100;
	ft_usleep(time_to_think, philo->table);
}

/* void	desync(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(30, philo->table);
	}
	else
	{
		if (philo->id % 2 == 0)
			think(philo, true);
	}
}

// V3
void	think(t_philo *philo, bool desync)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!desync)
		print_msg(philo, THINK);
	if (philo->table->philo_nbr % 2 == 0) // pair system fair
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	// action magique
	ft_usleep(t_think * 0.42, philo->table);
} */
