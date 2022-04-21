/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:11:44 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/21 17:22:13 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/* init all the non-forks mutexes useful for the simulation */

static int	init_mutexes(t_sim *sim)
{
	pthread_mutex_t		write_msg;
	pthread_mutex_t		add_meal_count;

	if (pthread_mutex_init(&write_msg, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&add_meal_count, NULL) != 0)
	{
		pthread_mutex_destroy(&write_msg);
		return (1);
	}
	sim->write_msg = write_msg;
	sim->add_meal_count = add_meal_count;
	return (0);
}

/* create an array of forks/mutexes (one by philo) 
and init them */

static pthread_mutex_t	*init_forks(t_sim *sim)
{
	pthread_mutex_t		*forks;
	int					i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			 * sim->nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < sim->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks); // destroy forks to avoid leaks ?
			return (NULL);
		}
		i++;
	}
	return (forks);
}

/* malloc an array of philo structs
setup this including the fork ids */

static t_philo	*init_philosophers(t_sim *sim)
{
	t_philo			*philos;
	int				i;

	philos = (t_philo *)malloc(sizeof(t_philo) * sim->nb_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < sim->nb_philo)
	{
		philos[i].id = i;
		philos[i].meal_num = 0;
		philos[i].last_eat = -1;
		philos[i].right_fork_id = i;
		if (sim->nb_philo != 1 && i > 0)
			philos[i].left_fork_id = i - 1;
		else if (sim->nb_philo != 1 && i == 0)
			philos[i].left_fork_id = sim->nb_philo - 1;
		else
			philos[i].left_fork_id = -1;
		philos[i].alive = 1;
		philos[i].sim = sim;
		i++;
	}
	return (philos);
}

void	init_sim_struct(t_sim *sim, char **argv, int argc)
{
	sim->nb_philo = (int)calc_res(argv[1]);
	sim->tt_die = (int)calc_res(argv[2]);
	sim->tt_eat = (int)calc_res(argv[3]);
	sim->tt_sleep = (int)calc_res(argv[4]);
	if (argc == 6)
		sim->win_cond = (int)calc_res(argv[5]);
	else
		sim->win_cond = -1;
	sim->time_eaten = 0;
	sim->endgame = 0;
	sim->start_sim = 0;
	sim->go_signal = 0;
	sim->philos = init_philosophers(sim);
	sim->forks = init_forks(sim);
	if (!sim->forks || !sim->philos)
		; // handle this
	if (init_mutexes(sim) != 0)
		; // handle this
	
}
