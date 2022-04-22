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

static void	rm_mutexes(t_sim *sim)
{
	int			i;
	
	pthread_mutex_destroy(&sim->add_meal_count);
	pthread_mutex_destroy(&sim->write_msg);
	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
}

int	clean_program(t_sim *sim)
{
	rm_mutexes(sim);
	free(sim->forks);
	sim->forks = NULL;
	free(sim->philos);
	sim->philos = NULL;
	free(sim);
	sim = NULL;
	return (0);
}
