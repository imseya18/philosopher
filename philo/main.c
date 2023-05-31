/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:30:29 by seya              #+#    #+#             */
/*   Updated: 2023/05/31 18:04:47 by mmorue           ###   ########.fr       */
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
		main->number_eat = 0;
	return (1);
}

long int	get_time(t_main *s_main, int cases, int philo_nb)
{
	long int	end_time;
	long int	actual_time;

	actual_time = 0;
	end_time = 0;
	gettimeofday(&(s_main->end), NULL);
	end_time = (s_main->end.tv_sec * 1000 + s_main->end.tv_usec / 1000);
	actual_time = (end_time - s_main->start_time);
	if (cases == 1)
		printf("%ld %d has taken a fork\n", actual_time, philo_nb);
	else if (cases == 2)
		printf("%ld %d is eating\n", actual_time, philo_nb);
	else if (cases == 3)
		printf("%ld %d is sleeping\n", actual_time, philo_nb);
	else if (cases == 4)
		printf("%ld %d is thinking\n", actual_time, philo_nb);
	else if (cases == 5)
		printf("%ld %d died\n", actual_time, philo_nb);
	return (actual_time);
}


void	*thread_routine(void *philippe)
{
	t_philo	*philo;
	t_main *main;

	philo = (t_philo *)philippe;
	main = philo->main;
		pthread_mutex_lock(&main->fork[0]);
		main->test++;
		printf("%d\n", main->test);
		pthread_mutex_unlock(&main->fork[0]);
	return (NULL);
}

void	init_philo(t_philo	*philo, t_main	*main)
{
	int	i;

	i = -1;
	philo = malloc(main->nb_philo * sizeof(pthread_t));
	main->fork = malloc(main->nb_philo * sizeof(t_fork));
	while(++i < main->nb_philo)
		pthread_mutex_init(&main->fork[i], NULL);
	i = -1;
	main->test = 0;
	while (++i < main->nb_philo)
	{
		philo[i].philo_nb = i;
		philo[i].main = main;
		pthread_create(&philo[i].philo_th, NULL, thread_routine, &philo[i]);
	}
	i = -1;
	while (++i < main->nb_philo)
	{
		pthread_join(philo[i].philo_th, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_main		main;

	philo = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("wrong number of arg \n");
		return (0);
	}
	else
	{
		if (init_variable(argv, &main) == 0)
			return (0);
		main.actual_philo = main.nb_philo;
		init_philo(philo, &main);
		//gettimeofday(philo->main.start), NULL);
		main.start_time = (main.start.tv_sec * 1000
				+ main.start.tv_usec / 1000);
		return (0);
	}
}
