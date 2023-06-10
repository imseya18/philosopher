/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:59:41 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/10 15:52:21 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	time_for_usleep(void)
{
	struct timeval	time;
	unsigned int	time_return;

	gettimeofday(&time, NULL);
	time_return = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time_return);
}

void	ft_usleep(int action_time, int eat, t_philo *philo)
{
	unsigned int	start_time;

	start_time = time_for_usleep();
	if (eat == 1)
	{
		pthread_mutex_lock(&philo->main->clone_time[philo->philo_nb]);
		philo->last_time_eat = time_for_usleep();
		pthread_mutex_unlock(&philo->main->clone_time[philo->philo_nb]);
	}
	while (time_for_usleep() - start_time < (unsigned int)action_time)
		usleep(200);
}

void	ft_print_case(t_main *main, int cases, int eat_number, int philo_nb)
{
	if (cases == 1 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d has taken a fork\n", main->actual_time,
			(philo_nb + 1));
	else if (cases == 2 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d is eating\n", main->actual_time, (philo_nb + 1));
	else if (cases == 3 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d is sleeping\n", main->actual_time, (philo_nb + 1));
	else if (cases == 4 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d is thinking\n", main->actual_time, (philo_nb + 1));
	else if (cases == 5 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d died\n", main->actual_time, (philo_nb + 1));
}

void	ft_print_case_two(t_main *main, int cases, int philo_nb)
{
	if (cases == 1 && main->stop == 0)
		printf("%ld %d has taken a fork\n", main->actual_time,
			(philo_nb + 1));
	else if (cases == 2 && main->stop == 0)
		printf("%ld %d is eating\n", main->actual_time, (philo_nb + 1));
	else if (cases == 3 && main->stop == 0)
		printf("%ld %d is sleeping\n", main->actual_time, (philo_nb + 1));
	else if (cases == 4 && main->stop == 0)
		printf("%ld %d is thinking\n", main->actual_time, (philo_nb + 1));
	else if (cases == 5 && main->stop == 0)
		printf("%ld %d died\n", main->actual_time, (philo_nb + 1));
}

void	get_time_print_action(t_main *main, int cases, t_philo *philo)
{
	long int	end_time;

	end_time = 0;
	pthread_mutex_lock(&main->alive);
	pthread_mutex_lock(&main->to_print);
	gettimeofday(&(main->end), NULL);
	end_time = (main->end.tv_sec * 1000 + main->end.tv_usec / 1000);
	main->actual_time = (end_time - main->start_time);
	if (main->number_eat != -1)
		ft_print_case(main, cases, philo->eat_number, philo->philo_nb);
	else
		ft_print_case_two(main, cases, philo->philo_nb);
	pthread_mutex_unlock(&main->alive);
	pthread_mutex_unlock(&main->to_print);
}
