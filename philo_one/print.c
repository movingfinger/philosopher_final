/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:39:41 by sako              #+#    #+#             */
/*   Updated: 2020/07/18 16:46:11 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_error(const char *str)
{
	ft_putendl(str);
	exit (0);
}

void	ft_display_param(const char *str, long long num, const char *unit)
{
	char	*number;

	number = ft_ltoa_base(num, 10);
	ft_putstr(str);
	ft_putstr(" ");
	ft_putstr(number);
	ft_putstr(" ");
	ft_putendl(unit);
	free(number);
}

void	print_input(t_status *status)
{
	ft_display_param("Die time is", status->time_to_die, "ms");
	ft_display_param("Eat time is", status->time_to_eat, "ms");
	ft_display_param("Sleep time is", status->time_to_sleep, "ms");
	ft_display_param("Number of philosopher is", status->num_philo, "total");
	if ( status->must_eat == 0)
		ft_putendl("food is unlimited");
	else
		ft_display_param("food limit per philosophers is", status->num_philo, "");
}

void	print_status(int stat)
{
	if (stat == ST_EAT)
		ft_putendl(" is eating");
	else if (stat == ST_SLEEP)
		ft_putendl(" is sleeping");
	else if (stat == ST_THINK)
		ft_putendl(" is thinking");
	else if (stat == ST_FORK)
		ft_putendl(" has taken a fork");
	else if (stat == ST_DIE)
		ft_putendl(" died");
	else if (stat == ST_DONE)
		ft_putendl(" finished to eat given food");
}

void	print_message(t_philosophers *philo, int stat)
{
	static int	finish = 0;
	char		*number;
	char		*id;

	pthread_mutex_lock(&philo->status->m_message);
	if (finish == 0)
	{
		number = ft_ltoa_base(timer() - philo->status->start_time, 10);
		id = ft_ltoa_base(philo->id + 1, 10);
		ft_putstr(number);
		ft_putstr(" ms - Philosopher ");
		if (stat != ST_DONE)
			ft_putstr(id);
		if (stat >= ST_DIE)
			finish = 1;
		print_status(stat);
		free(number);
		free(id);
	}
	pthread_mutex_unlock(&philo->status->m_message);
}