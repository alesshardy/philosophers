/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:04:12 by apintus           #+#    #+#             */
/*   Updated: 2024/06/17 16:31:25 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf
#include <stdlib.h> // malloc free
#include <unistd.h> //write usleep
#include <stdbool.h>
#include <pthread.h> // mutex: init destroy lock unlock
					 // threads : crate join detach
#include <sys/time.h> // gettimeofday
#include <limits.h>
#include <errno.h>

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

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_t_msg
{
	THINK,
	EAT,
	SLEEP,
	FORK,
	DIED,
}	t_msg;

// Code more Readeable
typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

typedef struct s_fork
{
	t_mtx	fork_mtx;
	int		id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals;
	bool		full;
	long		t_last_meal;
	t_fork		*left_forks;
	t_fork		*right_forks;
	pthread_t	thread;
	t_table		*table;
	t_mtx		philo_mtx;
}	t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	t_to_die;
	long	t_to_eat;
	long	t_to_sleep;
	long	max_meals;
	long	start_dinner;
	bool	dinner_finished;
	bool	thread_ready;
	long	thread_running;
	pthread_t	monitor; // death checker
	t_mtx	print_mtx;
	t_mtx	table_mtx;
	t_philo	*philos;
	t_fork	*forks;
}	t_table;

/*********** PROTOTYPES ***********/

// PARSING
int	parser(t_table *table, char **av);

// EXIT
char	*error_handler(char *str);

// INIT
int	ft_init(t_table *table);

// UTILS
long	get_time(t_time_code code);
void	wait_all_thread(t_table *table);
bool	dinner_finished(t_table *table);
void	my_usleep(long time, t_table *table);
void	clean(t_table *table);

// DINNER
void	dinner(t_table *table);

// MONITOR
void	*monitor(void *data);

// MSG
void	print_msg(t_philo *philo, t_msg msg);
