/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:57 by sako              #+#    #+#             */
/*   Updated: 2020/07/18 18:12:50 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	int i;
	t_philosophers *philo;

	set_param(av, ac);
	if (!(philo = (t_philosophers *)malloc(sizeof(t_philosophers) * num_philo)))
		ft_print_error("Fail to generate philosopher structure!");
	if (init_philo(philo))
		ft_print_error("Fail to initialize philo structure!");
	if (init_semaphore() || check_thread(philo) || begin_process(philo))
		return (clear_philosopher(philo));
	sem_wait(sem_dead);
	i = 0;
	while (i < num_philo)
		kill(philo[i++].pid, SIGKILL);
	clear_philosopher(philo);
	return (0);
}