/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:50 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/22 18:23:47 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_died(t_sim *sim, int i)
{
	sim->endgame++;
	display_msg(sim->philos[i].id, DEAD, sim);
}

static void	philos_have_eaten_enough(t_sim *sim)
{
	sim->endgame++;
	display_msg(1, VICTORY, sim);
}

static void	wait_for_endgame(t_sim *sim)
{
	int			i;

	while (!sim->endgame)
	{
		i = 0;
		while (i < sim->nb_philo)
		{
			if (get_time_now() >= sim->philos[i].last_eat + sim->tt_die
				&& sim->philos[i].last_eat != -1)
			{
				philo_died(sim, i);
				return ;
			}
			i++;
		}
		if (sim->time_eaten == sim->nb_philo)
		{
			philos_have_eaten_enough(sim);
			return ;
		}
		usleep(1000);
	}
}

/* create phi structs :
=> init all threads using pthread_create
=> put sim->phis_init = 1 (allow simulation to start)
=> use wait_for_endgame func to wait until end of sim
=> join threads
=> launch clean_program to suppress leaks and exit */

static int	init_philos_threads(t_sim *sim)
{
	int			i;

	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_create(&sim->philos[i].thread_id, NULL,
			&philo_routine, (void *)&sim->philos[i]);
		i++;
	}
	sim->start_sim = get_time_now();
	wait_for_endgame(sim);
	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}
	clean_program(sim, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int			valid;
	int			struct_status;
	t_sim		*sim;

	if (argc != 6 && argc != 5)
		return (display_error_msg(ARG_ERR));
	valid = check_args_validity(argc, argv);
	if (valid == 0)
		return (display_error_msg(INVAL_ERR));
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (display_error_msg(MALLOC_ERR));
	struct_status = init_sim_struct(sim, argv, argc);
	if (struct_status)
	{
		clean_program(sim, struct_status);
		return (1);
	}
	return (init_philos_threads(sim));
}
