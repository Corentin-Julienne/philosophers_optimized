/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:43 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/22 18:13:22 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* this function is used in order to prevent all philosophers
to take the right forks in the same time and
then causing a deadlock */

void	anti_deadlock_algo(t_philo *philo)
{
	if (philo->sim->nb_philo % 2 == 0)
	{
		if ((philo->id - 1) % 2 != 0)
			custom_usleep(philo->sim->tt_eat, philo->sim);
	}
	else
	{
		if (philo->sim->nb_philo == 1)
			return ;
		if ((philo->id - 1) % 2 != 0)
			custom_usleep(philo->sim->tt_eat, philo->sim);
		if (philo->id - 1 == philo->sim->nb_philo)
			custom_usleep(philo->sim->tt_eat * 2, philo->sim);
	}
}

int	is_dead(long long last_eat, long long tt_die)
{
	if (get_time_now() >= last_eat + tt_die)
		return (1);
	else
		return (0);
}

/* used to get the current timestamp !!! unit is milliseconds !!! */

long long	get_time_now(void) // ok
{
	struct timeval		timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

/* accurate usleep function
features a loop of usleep(50) with verif after each iteration
interrupts if : 
1) waiting time has reached its end
2) a philosopher died or the victory condition is achieved
!!! time in milliseconds !!! */

int	custom_usleep(long long time, t_sim *sim)
{
	long long		start;

	start = get_time_now();
	while (!sim->endgame)
	{
		if (get_time_now() - start >= time)
			return (0);
		usleep(200);
	}
	return (1);
}
