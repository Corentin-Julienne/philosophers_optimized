/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:23:32 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/21 18:00:41 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*deadly_routine(void *arg)
{
	
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	int				res_func;

	philo = (t_philo *)arg;
	res_func = 0;
	while (philo->sim->go_signal == 0)
		usleep(50);
	philo->last_eat = get_time_now();
	while (!res_func)
		res_func = eat_sleep_think_pattern(philo);
	return (NULL);
}
