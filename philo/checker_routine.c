/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:24 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/14 16:11:00 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker_routine(void *philippe)
{
	t_main	*main;

	main = (t_main *) philippe;
	while (1)
	{
		if (main->number_eat != -1)
			if (check_number_eat(main) == 1)
				break ;
		if (check_time_dead(main) == 1)
			break ;
		usleep(200);
	}
	return (NULL);
}

int	check_number_eat(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		pthread_mutex_lock(&main->check_time_eat);
		if (main->philo[i].eat_number < main->number_eat)
		{
			pthread_mutex_unlock(&main->check_time_eat);
			return (0);
		}
		pthread_mutex_unlock(&main->check_time_eat);
		i++;
	}
	pthread_mutex_lock(&main->alive);
	main->stop = 1;
	pthread_mutex_unlock(&main->alive);
	return (1);
}

int	check_time_dead(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nb_philo)
	{
		pthread_mutex_lock(&main->clone_time[i]);
		if ((time_for_usleep() - main->philo[i].last_time_eat)
			>= (unsigned int)main->to_die)
		{
			get_time_print_action(main, 5, &main->philo[i]);
			pthread_mutex_lock(&main->alive);
			main->stop = 1;
			pthread_mutex_unlock(&main->clone_time[i]);
			pthread_mutex_unlock(&main->alive);
			return (1);
		}
		pthread_mutex_unlock(&main->clone_time[i]);
	}
	return (0);
}
