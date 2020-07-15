/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 10:02:55 by sako              #+#    #+#             */
/*   Updated: 2020/07/15 12:41:33 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_token(t_philosophers *philo)
{
	sem_wait(philo->status->sem_num_can_eat);
}

void	return_token(t_philosophers *philo)
{
	sem_post(philo->status->sem_num_can_eat);
}

void	eat(t_philosophers *philo)
{
	sem_wait(philo->m_mutex);
	philo->is_eating = 1;
	philo->eat_time = timer();
	philo->check_time = philo->eat_time + philo->status->time_to_die;
	print_status(philo, ST_EAT);
	usleep(philo->status->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->m_mutex);
	sem_post(philo->m_eat);
}

void	grab_fork (t_philosophers *philo)
{
	sem_wait(philo->status->m_fork[philo->l_fork]);
	print_status(philo, ST_FORK);
	sem_wait(philo->status->m_fork[philo->r_fork]);
	print_status(philo, ST_FORK);
}

void	down_forks (t_philosophers *philo)
{
	print_status(philo, ST_SLEEP);
	sem_post(philo->status->m_fork[philo->l_fork]);
	sem_post(philo->status->m_fork[philo->r_fork]);
	usleep(philo->status->time_to_sleep * 1000);
}