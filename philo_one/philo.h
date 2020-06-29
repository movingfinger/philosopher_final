/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:49 by sako              #+#    #+#             */
/*   Updated: 2020/06/26 10:04:28 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include <sys/time.h>

# define ERR_NEG	"Negative numbers are not allowed! "\
					"You need to type positive numbers only!\n"
# define ERR_NONUM	"You must type nubmers only!\n"
# define ERR_ARG	"Argument should be 5 or 6\n"\
					"1. Number of Philosophers\n"\
					"2. Time to die\n"\
					"3. Time to eat\n"\
					"5. Time to sleep\n"\
					"4. Eat count for each philosophers [Optional]"
# define ERR_NUMMAX	"Philosophers should be between 0 to 200!"
# define ERR_INTMAX	"Argument 2 ~ 6 should not be over int max!"
# define L_FORK		"left"
# define R_FORK		"right"

# define ST_EAT		0
# define ST_SLEEP	1
# define ST_THINK	2
# define ST_FORK	3
# define ST_DIE		4
# define ST_DONE	5

// number of philosophers
// time to sleep
// time to eat
// time to die
// number of times each philosopher must eat. If -1, it means not defined.
// time at the beginning of program
// mutex for fork.

struct s_status;

typedef struct		s_philosophers
{
	int				id;
	int				is_eating;
	long long		check_time;
	long long		eat_time;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	struct s_status	*status;
	pthread_mutex_t	m_mutex;
	pthread_mutex_t	m_eat;
}					t_philosophers;

//	check_time is check whether philosopher failed to eat food in time or not.

typedef struct		s_status
{
	int				num_philo;
	long long		must_eat;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	t_philosophers	*philo;
	pthread_mutex_t	m_message;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	*m_fork;
}					t_status;

void				*check_food_count(void *temp_status);
void				*check_philosopher(void *temp_philo);
void				*philosopher (void *temp_philo);
void				do_philosopher(t_status *status);
void				free_status(t_status *status);

void				eat(t_philosophers *philo);
void				grab_fork (t_philosophers *philo);
void				down_forks (t_philosophers *philo);

void				error_check(char **av);
void				init_mutex(t_status *status);
void				init_philo(t_status *status);
void				set_param(int ac, char **av, t_status *status);

void				ft_print_error(const char *str);
void				print_input(t_status *status);
void				print_status(t_philosophers *philo, int stat);

long long			ft_atol (const char *str);
long long			timer(void);

#endif