/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:56:41 by apintus           #+#    #+#             */
/*   Updated: 2024/06/28 16:30:26 by apintus          ###   ########.fr       */
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
		time_to_think = philo->table->time_to_eat;
	ft_usleep(time_to_think, philo->table);
}
