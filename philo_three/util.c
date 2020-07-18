/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:59:28 by sako              #+#    #+#             */
/*   Updated: 2020/07/18 18:10:21 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atol (const char *str)
{
	int i;
	long long res;

	i = 0;
	res = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

void		ft_putstr(const char *str)
{
	for (int i = 0; str[i]; i++)
		write(1, &str[i], 1);
}

void		ft_putendl(const char *str)
{
	ft_putstr(str);
	ft_putstr("\n");
}

long long timer(void)
{
	static struct timeval var;
	long long time;

	gettimeofday(&var, NULL);
	time = var.tv_sec * (long long )1000 + var.tv_usec / 1000;
	return (time);
}