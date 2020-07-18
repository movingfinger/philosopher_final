/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:39:41 by sako              #+#    #+#             */
/*   Updated: 2020/07/18 18:26:07 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print_error(const char *str)
{
	ft_putendl(str);
	exit (0);
}

void get_message(int num)
{
	if (num == 0)
		ft_putendl(" is eating");
	else if (num == 1)
		ft_putendl(" is sleeping");
	else if (num == 2)
		ft_putendl(" has taken a fork");
	else if (num == 3)
		ft_putendl(" is thinking");
	else if (num == 5)
		ft_putendl(" food limit reached");
	else
		ft_putendl(" died");
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

void	print_input(void)
{
	ft_display_param("Number of philosopher is", num_philo, "total");
	ft_display_param("Die time is", die_seconds, "ms");
	ft_display_param("Eat time is", eat_seconds, "ms");
	ft_display_param("Sleep time is", sleep_seconds, "ms");
	if (food_limit == 0)
		ft_putendl("food is unlimited");
	else
		ft_display_param("food limit per philosophers is", num_philo, "");
}
void	print_message(t_philosophers *philo, int num)
{
	char	*number;
	char	*id;

	number = ft_ltoa_base(timer() - start_time, 10);
	id = ft_ltoa_base(philo->pos + 1, 10);
	sem_wait(sem_print);
	sem_wait(sem_dead_report);
	ft_putstr(number);
	ft_putstr(" ms - Philosopher ");
	if (num != 5)
		ft_putstr(id);
	get_message(num);
	if (num < 4)
		sem_post(sem_dead_report);
	sem_post(sem_print);
	free(number);
	free(id);
}

char	*make_semaphore(const char *str, int i)
{
	char	*c_sem;
	char	*pos;
	int		len;

	pos = ft_ltoa_base(i, 10);
	len = ft_strlen(str) + ft_strlen(pos);
	c_sem = ft_strnew(len);
	ft_strlcat(c_sem, str, len);
	ft_strlcat(c_sem, pos, len);
	sem_unlink(c_sem);
	free(pos);
	return (c_sem);
}