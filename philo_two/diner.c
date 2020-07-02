/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 10:02:55 by sako              #+#    #+#             */
/*   Updated: 2020/07/02 19:15:47 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosophers *philo)
{
	sem_wait(philo->sem_mutex);
	philo->is_eating = 1;
	philo->eat_time = timer();
	philo->check_time = philo->eat_time + philo->status->time_to_die;
	if (print_status(philo, ST_EAT))
		ft_print_error("eat wrong!");
	usleep(philo->status->time_to_eat * 1000);
	//ft_usleep(philo->status->time_to_eat * 1000);
	//nanosleep(&n_time, NULL);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->sem_mutex);
	sem_post(philo->sem_eat);
}

void	grab_fork (t_philosophers *philo)
{
	sem_wait(philo->status->sem_fork);
	if (print_status(philo, ST_FORK))
		ft_print_error("Grab fork wrong!");
	sem_wait(philo->status->sem_fork);
	if (print_status(philo, ST_FORK))
		ft_print_error("Grab fork wrong!");
}

void	down_forks (t_philosophers *philo)
{
	if (print_status(philo, ST_SLEEP))
		ft_print_error("Down fork wrong!");
	sem_post(philo->status->sem_fork);
	sem_post(philo->status->sem_fork);
	usleep(philo->status->time_to_sleep * 1000);
	//ft_usleep(philo->status->time_to_sleep * 1000);
	//nanosleep(&n_time, NULL);
}