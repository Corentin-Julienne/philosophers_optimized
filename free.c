/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:48 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/22 17:20:30 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* free all the mutexes when program exit without syscall failure */

void	clean_program(t_sim *sim, int code)
{
	int			i;
	
	if (code != 2)
	{
		pthread_mutex_destroy(&sim->add_meal_count);
		pthread_mutex_destroy(&sim->write_msg);
	}	
	if (sim->forks)
	{
		i = 0;
		while (i < sim->nb_philo)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
		sim->forks = NULL;
	}
	if (sim->philos)
	{
		free(sim->philos);
		sim->philos = NULL;
	}
	free(sim);
	sim = NULL;
}
