/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seya <seya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:30:29 by seya              #+#    #+#             */
/*   Updated: 2023/06/06 02:35:23 by seya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

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

long int	get_time_print_action(t_main *s_main, int cases, int philo_nb)
{
	long int	end_time;
	long int	actual_time;

	actual_time = 0;
	end_time = 0;
	pthread_mutex_lock(&s_main->to_print);
	gettimeofday(&(s_main->end), NULL);
	end_time = (s_main->end.tv_sec * 1000 + s_main->end.tv_usec / 1000);
	actual_time = (end_time - s_main->start_time);
	if (cases == 1)
		printf("%ld %d has taken a fork\n", actual_time, (philo_nb + 1));
	else if (cases == 2)
		printf("%ld %d is eating\n", actual_time, (philo_nb + 1));
	else if (cases == 3)
		printf("%ld %d is sleeping\n", actual_time, (philo_nb + 1));
	else if (cases == 4)
		printf("%ld %d is thinking\n", actual_time, (philo_nb + 1));
	else if (cases == 5)
		printf("%ld %d died\n", actual_time, (philo_nb + 1));
	pthread_mutex_unlock(&s_main->to_print);
	return (actual_time);
}

//int	check_if_alive(t_philo	*philo)
//{
//	if(philo->alive == 0)
//		return (1);
//	return (0);
//}

void	philo_eating(t_philo *philo, t_main *main)
{
	if (philo->philo_nb == 0)
	{
		pthread_mutex_lock(&main->fork[main->nb_philo - 1]);
		get_time_print_action(main, 1, philo->philo_nb);
		pthread_mutex_lock(&main->fork[philo->philo_nb]);
		get_time_print_action(main, 1, philo->philo_nb);
		get_time_print_action(main, 2, philo->philo_nb);
		ft_usleep(main->to_eat);
		pthread_mutex_unlock(&main->fork[main->nb_philo - 1]);
		pthread_mutex_unlock(&main->fork[philo->philo_nb]);
	}
	else
	{
		pthread_mutex_lock(&main->fork[(philo->philo_nb - 1)]);
		get_time_print_action(main, 1, philo->philo_nb);
		pthread_mutex_lock(&main->fork[philo->philo_nb]);
		get_time_print_action(main, 1, philo->philo_nb);
		get_time_print_action(main, 2, philo->philo_nb);
		ft_usleep(main->to_eat);
		pthread_mutex_unlock(&main->fork[(philo->philo_nb - 1)]);
		pthread_mutex_unlock(&main->fork[philo->philo_nb]);
	}
}

void	philo_sleep_think(t_philo *philo, t_main *main)
{
	get_time_print_action(main, 3, philo->philo_nb);
	ft_usleep(main->to_sleep);
	get_time_print_action(main, 4, philo->philo_nb);
}

void	*thread_routine(void *philippe)
{
	t_philo	*philo;
	t_main *main;

	philo = (t_philo *)philippe;
	main = philo->main;
	while(main->stop == 0)
	{
		//if(main->number_eat != -1 && )
		philo_eating(philo, main);
		philo_sleep_think(philo, main);
	}
	return (NULL);
}

void	init_philo(t_main	*main)
{
	int	i;

	i = -1;
	main->philo = malloc(main->nb_philo * sizeof(pthread_t));
	main->fork = malloc(main->nb_philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&main->to_print, NULL);
	pthread_mutex_init(&main->check_alive, NULL);
	while(++i < main->nb_philo)
		pthread_mutex_init(&main->fork[i], NULL);
	i = -1;
	while (++i < main->nb_philo)
	{
		main->philo[i].philo_nb = i;
		main->philo[i].main = main;
		main->philo[i].last_time_eat = 0;
		main->philo[i].eat_number = 0;
		pthread_create(&main->philo[i].philo_th, NULL, thread_routine, &main->philo[i]);
	}
	i = -1;
	while (++i < main->nb_philo)
		pthread_join(main->philo[i].philo_th, NULL);
}

int	main(int argc, char **argv)
{
	//t_philo		*philo;
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
		return (0);
	}
}
