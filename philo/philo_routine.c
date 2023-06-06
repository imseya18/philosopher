/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:29:57 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/06 16:25:49 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *philippe)
{
	t_philo	*philo;
	t_main	*main;

	philo = (t_philo *)philippe;
	main = philo->main;
	while (main->stop == 0)
	{
		if (main->number_eat != -1 && check_number_eat(main) == 1)
			break ;
		philo_eating(philo, main);
		philo_sleep_think(philo, main);
	}
	return (NULL);
}

void	add_time_they_eat(t_philo *philo, t_main *main)
{
	pthread_mutex_lock(&main->check_time_eat);
	philo->eat_number++;
	pthread_mutex_unlock(&main->check_time_eat);
}

void	philo_sleep_think(t_philo *philo, t_main *main)
{
	get_time_print_action(main, 3, philo->philo_nb, 0);
	ft_usleep(main->to_sleep);
	get_time_print_action(main, 4, philo->philo_nb, 0);
}

void	philo_eating(t_philo *philo, t_main *main)
{
	if (philo->philo_nb == 0)
	{
		pthread_mutex_lock(&main->fork[main->nb_philo - 1]);
		get_time_print_action(main, 1, philo->philo_nb, main->nb_philo - 1);
		pthread_mutex_lock(&main->fork[philo->philo_nb]);
		get_time_print_action(main, 1, philo->philo_nb, philo->philo_nb);
		get_time_print_action(main, 2, philo->philo_nb, 0);
		add_time_they_eat(philo, main);
		ft_usleep(main->to_eat);
		pthread_mutex_unlock(&main->fork[main->nb_philo - 1]);
		pthread_mutex_unlock(&main->fork[philo->philo_nb]);
	}
	else
	{
		pthread_mutex_lock(&main->fork[(philo->philo_nb - 1)]);
		get_time_print_action(main, 1, philo->philo_nb, philo->philo_nb - 1);
		pthread_mutex_lock(&main->fork[philo->philo_nb]);
		get_time_print_action(main, 1, philo->philo_nb, philo->philo_nb);
		get_time_print_action(main, 2, philo->philo_nb, 0);
		add_time_they_eat(philo, main);
		ft_usleep(main->to_eat);
		pthread_mutex_unlock(&main->fork[(philo->philo_nb - 1)]);
		pthread_mutex_unlock(&main->fork[philo->philo_nb]);
	}
}
