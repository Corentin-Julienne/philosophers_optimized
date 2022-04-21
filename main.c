/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:50 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/21 18:04:35 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_died(t_sim *sim, long long i)
{
	display_msg(phis[i].id, DEAD, &phis[i]);
	pthread_mutex_lock(&phis->mutexes->stop_game);
	phis->sim->endgame++;
	pthread_mutex_unlock(&phis->mutexes->stop_game);
}

static void	wait_for_endgame(t_sim *sim)
{
	long long		i;

	while (!sim->endgame)
	{
		i = 0;
		while (i < sim->nb_philo)
		{
			if ((get_time_now() >= (sim->philos[i].last_eat + sim->tt_die))
				 && phis[i].last_eat != -1)
			{
				phi_has_died(phis, i);
				break ;
			}
			else if (sim->time_eaten == sim->nb_philo)
			{
				phis_have_eaten(phis, i);
				break ;
			}
			i++;
		}
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
	long long			i;

	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_create(&sim->philos[i].thread_id, NULL,
			 &philo_routine, (void *)&sim->philos[i]);
		i++;
	}
	sim->go_signal = 1;
	sim->start_sim = get_time_now();
	wait_for_endgame(sim);
	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}
	return (clean_program(sim));
}

int	main(int argc, char **argv)
{
	int			valid;
	t_sim		*sim;
	
	if (argc != 6 && argc != 5)
		return (display_error_msg("wrong number of arguments\n"));
	valid = check_args_validity(argc, argv); // yet to test
	if (valid == 0)
		return (display_error_msg("invalid argument format\n"));
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (display_error_msg("unsuccessful memory allocation\n"));
	init_sim_struct(sim, argv, argc);
	init_philos_threads(sim);
	return (0);
}