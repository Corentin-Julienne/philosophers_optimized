/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:48:46 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/22 13:11:42 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	display_error_msg(const char *err_specific)
{
	char		*err_general;

	err_general = "Philosophers : error : ";
	write(STDERR_FILENO, err_general, ft_strlen(err_general));
	write(STDERR_FILENO, err_specific, ft_strlen(err_specific));
	return (1);
}

static void	print_msg(int id, int msg_type, t_sim *sim)
{
	char			*msg;
	long long 		time;

	if (msg_type == THINKING)
		msg = "is thinking\n";
	else if (msg_type == EATING)
		msg = "is eating\n";
	else if (msg_type == SLEEPING)
		msg = "is sleeping\n";
	else if (msg_type == DEAD)
		msg = "died\n";
	else
		msg = "has taken a fork\n";
	time = get_time_now() - sim->start_sim;
	printf("%lli %i %s", time, id, msg);
}

/* display msg function will print a msg for a changing state
(eat, sleep, think, dead, victory). The stop static variable,
shared by all threads,
is used as a bareer to prevent multiple philos
to win the game or die at the same time */

int	display_msg(int id, int msg_type, t_sim *sim)
{
	static int		stop = 0;

	pthread_mutex_lock(&sim->write_msg);
	if (stop == 0)
	{
		if (msg_type == DEAD || msg_type == VICTORY)
			stop++;
		if (msg_type == VICTORY)
		{
			pthread_mutex_unlock(&sim->write_msg);
			return (stop);
		}
		print_msg(id, msg_type, sim);
	}
	pthread_mutex_unlock(&sim->write_msg);
	return (stop);
}
