/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:29:57 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/08 18:42:33 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *philippe)
{
	t_philo		*philo;
	t_main		*main;
	pthread_t	dead_or_not;

	philo = (t_philo *)philippe;
	main = philo->main;
	if (philo->philo_nb % 2 != 0)
		usleep(100);
	while (check_if_dead(main) != 1)
	{
		pthread_create(&dead_or_not, NULL, dead_routine, philo);
		philo_eating(philo, main);
		if (check_if_dead(main) == 1)
		{
			pthread_detach(dead_or_not);
			break ;
		}
		philo_sleep_think(philo, main);
		pthread_detach(dead_or_not);
	}
	return (NULL);
}

void	*dead_routine(void	*philippe)
{
	t_philo			*philo;
	unsigned int	time;

	philo = (t_philo *)philippe;
	ft_usleep(philo->main->to_die, 0, NULL);
	pthread_mutex_lock(&philo->main->clone_time);
	time = philo->last_time_eat;
	pthread_mutex_unlock(&philo->main->clone_time);
	if (time_for_usleep() - time >= (unsigned int)philo->main->to_die)
	{
		get_time_print_action(philo->main, 5, philo, 0);
		pthread_mutex_lock(&philo->main->alive);
		philo->main->stop = 1;
		pthread_mutex_unlock(&philo->main->alive);
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
	if (stoped == 1)
		return (stoped);
	if (main->number_eat != -1)
		check_number_eat(main);
	pthread_mutex_lock(&main->alive);
	stoped = main->stop;
	pthread_mutex_unlock(&main->alive);
	return (stoped);
}

void	add_time_they_eat(t_philo *philo, t_main *main)
{
	pthread_mutex_lock(&main->check_time_eat);
	philo->eat_number++;
	pthread_mutex_unlock(&main->check_time_eat);
}

void	philo_sleep_think(t_philo *philo, t_main *main)
{
	get_time_print_action(main, 3, philo, 0);
	ft_usleep(main->to_sleep, 0, NULL);
	get_time_print_action(main, 4, philo, 0);
}

void	philo_eating(t_philo *philo, t_main *main)
{
	if (philo->philo_nb == 0)
	{
		pthread_mutex_lock(&main->fork[main->nb_philo - 1]);
		get_time_print_action(main, 1, philo, main->nb_philo - 1);
		pthread_mutex_lock(&main->fork[philo->philo_nb]);
		get_time_print_action(main, 1, philo, philo->philo_nb);
		get_time_print_action(main, 2, philo, 0);
		add_time_they_eat(philo, main);
		ft_usleep(main->to_eat, 1, philo);
		pthread_mutex_unlock(&main->fork[main->nb_philo - 1]);
		pthread_mutex_unlock(&main->fork[philo->philo_nb]);
	}
	else
	{
		pthread_mutex_lock(&main->fork[(philo->philo_nb - 1)]);
		get_time_print_action(main, 1, philo, philo->philo_nb - 1);
		pthread_mutex_lock(&main->fork[philo->philo_nb]);
		get_time_print_action(main, 1, philo, philo->philo_nb);
		get_time_print_action(main, 2, philo, 0);
		add_time_they_eat(philo, main);
		ft_usleep(main->to_eat, 1, philo);
		pthread_mutex_unlock(&main->fork[(philo->philo_nb - 1)]);
		pthread_mutex_unlock(&main->fork[philo->philo_nb]);
	}
}
