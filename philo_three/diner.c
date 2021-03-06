/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 18:12:19 by sako              #+#    #+#             */
/*   Updated: 2020/07/18 18:12:33 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philosophers *philo)
{
	sem_wait(sem_fork);
	print_message(philo, 2);
	sem_wait(sem_fork);
	print_message(philo, 2);
}

void	drop_forks(t_philosophers *philo)
{
	print_message(philo, 1);
	sem_post(sem_fork);
	sem_post(sem_fork);
	usleep(sleep_seconds * 1000);
}

void	eat(t_philosophers *philo)
{
	philo->state = 0;
	philo->last_time = timer();
	philo->limit = philo->last_time + die_seconds;
	print_message(philo, 0);
	usleep(eat_seconds * 1000);
	philo->eat_count++;
	philo->state = 1;
	sem_post(philo->food_count);
}