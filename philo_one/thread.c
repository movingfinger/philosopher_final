/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:58:10 by sako              #+#    #+#             */
/*   Updated: 2020/06/30 13:09:41 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_food_count(void *temp_status)
{
	t_status *status;

	status = (t_status *)temp_status;
	for (int i = 0; i < status->must_eat; i++)
	{
		for (int j = 0; j < status->num_philo; j++)
			pthread_mutex_lock(&status->philo[j].m_eat);
	}
	print_status(&status->philo[0], ST_DONE);
	pthread_mutex_unlock(&status->m_dead);
	return ((void *)0);
}

void	*check_philosopher(void *temp_philo)
{
	t_philosophers *philo;
	long long time;

	philo = (t_philosophers *)temp_philo;
	while (1)
	{
		time = timer();
		//time = timer() - philo->status->start_time;
		pthread_mutex_lock(&philo->m_mutex);
		if (!philo->is_eating && time > philo->check_time)
		{
			print_status(philo, ST_DIE);
			pthread_mutex_unlock(&philo->m_mutex);
			pthread_mutex_unlock(&philo->status->m_dead);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->m_mutex);
		usleep(1000);
	}
}

void	*philosopher (void *temp_philo)
{
	t_philosophers	*philo;
	pthread_t		t_id;

	philo = (t_philosophers *)temp_philo;
	//philo->eat_time = timer() - philo->status->start_time;
	philo->eat_time = timer();
	philo->check_time = philo->eat_time + philo->status->time_to_die;
	if (pthread_create(&t_id, NULL, check_philosopher, temp_philo) != 0)
		ft_print_error("Failed to create check philosopher thread!");
	pthread_detach(t_id);
	while (1)
	{
		grab_fork(philo);
		eat(philo);
		down_forks(philo);
		print_status(philo, ST_THINK);
	}
	return ((void *)0);
}

void	do_philosopher(t_status *status)
{
	int			i;
	pthread_t	t_id;
	void		*philo;

	status->start_time = timer();
	if (status->must_eat > 0)
	{
		if (pthread_create(&t_id, NULL, &check_food_count, (void *)status) != 0)
			ft_print_error("Failed to make food count thread!");
		pthread_detach(t_id);
	}
	for (i = 0; i < status->num_philo; i++)
	{
		philo = (void *)(&status->philo[i]);
		if (pthread_create(&t_id, NULL, &philosopher, philo) != 0)
			ft_print_error("Failed to make philosopher thread!");
		pthread_detach(t_id);
		usleep(100);
	}
	pthread_mutex_lock(&status->m_dead);
	pthread_mutex_unlock(&status->m_dead);
	free_status(status);
}

void	free_status(t_status *status)
{
	if (status->m_fork)
	{
		for (int i = 0; i < status->num_philo; i++)
			pthread_mutex_destroy(&status->m_fork[i]);
		free(status->m_fork);
	}
	if (status->philo)
	{
		for (int i = 0; i < status->num_philo; i++)
		{
			pthread_mutex_destroy(&status->philo[i].m_mutex);
			pthread_mutex_destroy(&status->philo[i].m_eat);
		}
		free(status->philo);
	}
	pthread_mutex_destroy(&status->m_message);
	pthread_mutex_destroy(&status->m_dead);
}