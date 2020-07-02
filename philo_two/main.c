/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:57 by sako              #+#    #+#             */
/*   Updated: 2020/07/02 13:43:41 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_status status;
	
	gettimeofday(&t_time, NULL);
	set_param(ac, av, &status);
	do_philosopher(&status);
	return (0);
}
