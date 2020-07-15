/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:58:10 by sako              #+#    #+#             */
/*   Updated: 2020/07/15 20:51:07 by sako             ###   ########.fr       */
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
			sem_wait(status->philo[j].m_eat);
	}
	print_status(&status->philo[0], ST_DONE);
	sem_post(status->m_dead);
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
		sem_wait(philo->m_mutex);
		if (!philo->is_eating && time > philo->check_time)
		{
			print_status(philo, ST_DIE);
			sem_post(philo->m_mutex);
			sem_post(philo->status->m_dead);			
			return ((void *)0);
		}
		sem_post(philo->m_mutex);
		usleep(1000);
	}
}

void	*philosopher (void *temp_philo)
{
	t_philosophers	*philo;
	pthread_t		t_id;

	philo = (t_philosophers *)temp_philo;
	philo->eat_time = timer();
	philo->check_time = philo->eat_time + philo->status->time_to_die;
	if (pthread_create(&t_id, NULL, check_philosopher, temp_philo) != 0)
		ft_print_error("Failed to create check philosopher thread!");
	pthread_detach(t_id);
	while (1)
	{
		//get_token(philo);
		grab_fork(philo);
		eat(philo);
		down_forks(philo);
		print_status(philo, ST_THINK);
		//return_token(philo);
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
	}
	sem_wait(status->m_dead);
	sem_post(status->m_dead);
	free_status(status);
}

void	free_status(t_status *status)
{
	char	*c_sem;
	sem_unlink("SEM_MESSAGE");
	sem_unlink("SEM_DEAD");
	sem_unlink("SEM_NUM_CAN_EAT");
	if (status->m_fork)
	{
		for (int i = 0; i < status->num_philo; i++)
		{
			c_sem = make_semaphore("SEM_FORK", i);
			sem_unlink(c_sem);
			//free (status->m_fork[i]);
		}
		free(status->m_fork);
	}
	if (status->philo)
	{
		for (int i = 0; i < status->num_philo; i++)
		{
			c_sem = make_semaphore("SEM_PHILO", i);
			sem_unlink(c_sem);
			c_sem = make_semaphore("SEM_FOOD", i);
			sem_unlink(c_sem);
		}
		free(status->philo);
	}
	if (c_sem)
		free(c_sem);
}