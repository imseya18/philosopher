/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:30:29 by seya              #+#    #+#             */
/*   Updated: 2023/06/10 15:47:24 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_variable(char **argv, t_main *main)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (check_if_digit(argv[i]) == 0)
		{
			printf("error one of the argument isn't a digit\n");
			return (0);
		}
	}
	main->nb_philo = atoi(argv[1]);
	if (main->nb_philo < 1)
	{
		printf("error wrong number of philo\n");
		return (0);
	}
	main->to_die = atoi(argv[2]);
	main->to_eat = atoi(argv[3]);
	main->to_sleep = atoi(argv[4]);
	if (argv[5])
		main->number_eat = atoi(argv[5]);
	else
		main->number_eat = -1;
	return (1);
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

void	ft_destructor(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nb_philo)
	{
		pthread_mutex_destroy(&main->fork[i]);
		pthread_mutex_destroy(&main->clone_time[i]);
	}
	pthread_mutex_destroy(&main->to_print);
	pthread_mutex_destroy(&main->alive);
	pthread_mutex_destroy(&main->check_time_eat);
}

void	init_philo(t_main	*main)
{
	int	i;

	i = -1;
	main->philo = ftm_malloc(main->nb_philo * sizeof(t_philo));
	main->fork = ftm_malloc(main->nb_philo * sizeof(pthread_mutex_t));
	main->clone_time = ftm_malloc(main->nb_philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&main->to_print, NULL);
	pthread_mutex_init(&main->alive, NULL);
	pthread_mutex_init(&main->check_time_eat, NULL);
	while (++i < main->nb_philo)
	{
		pthread_mutex_init(&main->fork[i], NULL);
		pthread_mutex_init(&main->clone_time[i], NULL);
	}
	i = -1;
	while (++i < main->nb_philo)
	{
		main->philo[i].philo_nb = i;
		main->philo[i].main = main;
		main->philo[i].last_time_eat = 0;
		main->philo[i].eat_number = 0;
		pthread_create(&main->philo[i].philo_th, NULL, thread_routine,
			&main->philo[i]);
	}
	i = -1;
	while (++i < main->nb_philo)
		pthread_join(main->philo[i].philo_th, NULL);
	ft_destructor(main);
}

int	main(int argc, char **argv)
{
	t_main		main;

	main.philo = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("wrong number of arg \n");
		return (0);
	}
	else
	{
		if (init_variable(argv, &main) == 0)
			return (0);
		main.stop = 0;
		gettimeofday(&(main.start), NULL);
		main.start_time = (main.start.tv_sec * 1000
				+ main.start.tv_usec / 1000);
		init_philo(&main);
		ftm_free_all();
		return (0);
	}
}
