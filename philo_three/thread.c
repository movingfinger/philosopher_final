/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:58:10 by sako              #+#    #+#             */
/*   Updated: 2020/07/18 18:17:01 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_count(void *t_philo)
{
	int	total;
	int	i;
	t_philosophers *philo;

	total = 0;
	philo = (t_philosophers *)t_philo;
	while (total < food_limit)
	{
		i = 0;
		while (i < num_philo)
		{
			sem_wait(philo[i].food_count);
			i++;
		}
		total++;
	}
	print_message(&philo[0], 5);
	sem_post(sem_dead);
	return ((void *)0);
}

int		check_thread(t_philosophers *philo)
{
	pthread_t	tid;

	if (food_limit > -1)
	{
		if (pthread_create(&tid, NULL, &check_count, (void *)philo) != 0)
			ft_print_error("Failed to creata check thread!");
		pthread_detach(tid);
	}
	return (0);
}

void	*check_process(void *t_philo)
{
	t_philosophers *philo;

	philo = (t_philosophers *)t_philo;
	while (1)
	{
		sem_wait(philo->sem);
		if (!(philo->state == 0) && timer() > philo->limit)
		{
			print_message(philo, 4);
			sem_post(philo->sem);
			sem_post(sem_dead);
			return ((void *)0);
		}
		sem_post(philo->sem);
		usleep(1000);
	}
	return ((void *)0);
}

int		do_process(t_philosophers *philo)
{
	t_philosophers	*t_philo;
	pthread_t		tid;

	t_philo = (t_philosophers *)philo;
	t_philo->last_time = timer();
	t_philo->limit = t_philo->last_time + die_seconds;
	if (pthread_create(&tid, NULL, &check_process, philo) != 0)
		ft_print_error("Failed to generate thread for process!");
	pthread_detach(tid);
	while (1)
	{
		sem_wait(sem_pickup);
		grab_forks(philo);
		sem_post(sem_pickup);
		eat(philo);
		drop_forks(philo);
		print_message(philo, 3);
	}
}

int		begin_process(t_philosophers *philo)
{
	int		i;

	start_time = timer();
	i = 0;
	while (i < num_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			ft_print_error("Failed to fork child process!");
		else if (philo[i].pid == 0)
		{
			do_process(&philo[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}
