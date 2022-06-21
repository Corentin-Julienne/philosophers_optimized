/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:23:32 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/22 16:21:24 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	int				res_func;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->sim->add_ready);
	philo->sim->phi_ready++;
	pthread_mutex_unlock(&philo->sim->add_ready);
	while (philo->sim->start_sim == -1)
		usleep(1);
	philo->last_eat = get_time_now();
	anti_deadlock_algo(philo);
	res_func = 0;
	while (!res_func)
		res_func = eat_sleep_think_pattern(philo);
	return (NULL);
}
