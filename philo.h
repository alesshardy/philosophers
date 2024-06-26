/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:13:56 by apintus           #+#    #+#             */
/*   Updated: 2024/07/01 12:45:44 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

/*********** STRUCTURES ***********/

// Color
# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

typedef enum e_t_msg
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIED,
}	t_msg;

// Code more Readeable
typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct s_data_time
{
	size_t	start;
	size_t	now;
	size_t	remaining;
	size_t	sleep_time;
}	t_data_time;

typedef struct s_philo
{
	long		id;
	long		position;
	pthread_t	thread;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	long		last_meal;
	long		count_meal;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	t_philo		*philos;
	pthread_t	monitor;
	t_mtx		*forks;
	t_mtx		dead_mtx;
	t_mtx		count_meal_mtx;
	t_mtx		print_mtx;
	t_mtx		last_meal_mtx;
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meal_nbr;
	long		time_start_dinner;
	int			dead;
}	t_table;

/*********** PROTOTYPES ***********/

// LIBFT
void	ft_putstr_fd(char *s, int fd);
int		is_digit(int c);
int		is_space(char c);
long	ft_strlen(const char *s);

// PARSING
int		parser(int ac, char **av, t_table *table);

// INIT
int		init_table(t_table *table);
int		init_mutex(t_table *table);

// UTILS
size_t	get_time(void);
void	ft_usleep(size_t time, t_table *table);
void	print_msg(t_philo *philo, int msg);
void	cleanning(t_table *table);
void	wait_all_threads(size_t time);

// ACTIONS
void	eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	think(t_philo *philo);

// MONITOR
int		dinner_end(t_table *table);
void	set_death(t_table *table);
int		check_death(t_philo *philo);
int		handle_end(t_table *table);
void	*monitor(void *arg);

#endif
