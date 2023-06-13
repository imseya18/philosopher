/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:29:57 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/13 18:10:46 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *philippe)
{
	t_philo		*philo;
	t_main		*main;

	philo = (t_philo *)philippe;
	main = philo->main;
	if (main->nb_philo == 1)
	{
		get_time_print_action(main, 1, philo);
		return (NULL);
	}
	if (philo->philo_nb % 2 == 0)
		usleep(main->to_eat);
	while (check_if_dead(main) != 1)
	{
		philo_eating(philo, main);
		philo_sleep_think(philo, main);
	}
	return (NULL);
}

int	check_if_dead(t_main *main)
{
	int	stoped;

	stoped = 0;
	pthread_mutex_lock(&main->alive);
	stoped = main->stop;
	pthread_mutex_unlock(&main->alive);
	return (stoped);
}

void	philo_sleep_think(t_philo *philo, t_main *main)
{
	get_time_print_action(main, 3, philo);
	ft_usleep(main->to_sleep, 0, NULL);
	get_time_print_action(main, 4, philo);
}

void	philo_eating(t_philo *philo, t_main *main)
{
	if (philo->philo_nb == 0)
	{
		pthread_mutex_lock(&main->fork[main->nb_philo - 1]);
		get_time_print_action(main, 1, philo);
		pthread_mutex_lock(&main->fork[philo->philo_nb]);
		get_time_print_action(main, 1, philo);
		get_time_print_action(main, 2, philo);
		add_time_they_eat(philo, main);
		ft_usleep(main->to_eat, 1, philo);
		pthread_mutex_unlock(&main->fork[main->nb_philo - 1]);
		pthread_mutex_unlock(&main->fork[philo->philo_nb]);
	}
	else
	{
		pthread_mutex_lock(&main->fork[(philo->philo_nb - 1)]);
		get_time_print_action(main, 1, philo);
		pthread_mutex_lock(&main->fork[philo->philo_nb]);
		get_time_print_action(main, 1, philo);
		get_time_print_action(main, 2, philo);
		add_time_they_eat(philo, main);
		ft_usleep(main->to_eat, 1, philo);
		pthread_mutex_unlock(&main->fork[(philo->philo_nb - 1)]);
		pthread_mutex_unlock(&main->fork[philo->philo_nb]);
	}
}
