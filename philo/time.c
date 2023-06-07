/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seya <seya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:59:41 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/08 00:10:50 by seya             ###   ########.fr       */
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
		philo->last_time_eat = time_for_usleep();
	while (time_for_usleep() - start_time < (unsigned int)action_time)
		usleep(200);
}

long int	get_time_print_action(t_main *main, int cases, int philo_nb, int eat_number,int fork_number) //retirer fork number
{
	long int	end_time;
	long int	actual_time;

	actual_time = 0;
	end_time = 0;
	pthread_mutex_lock(&main->alive);
	pthread_mutex_lock(&main->to_print);
	gettimeofday(&(main->end), NULL);
	end_time = (main->end.tv_sec * 1000 + main->end.tv_usec / 1000);
	actual_time = (end_time - main->start_time);
	if (cases == 1 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d has taken a fork %d\n", actual_time, (philo_nb + 1), (fork_number + 1));
	else if (cases == 2 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d is eating\n", actual_time, (philo_nb + 1));
	else if (cases == 3 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d is sleeping\n", actual_time, (philo_nb + 1));
	else if (cases == 4 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d is thinking\n", actual_time, (philo_nb + 1));
	else if (cases == 5 && main->stop == 0 && eat_number < main->number_eat)
		printf("%ld %d died\n", actual_time, (philo_nb + 1));
	pthread_mutex_unlock(&main->alive);
	pthread_mutex_unlock(&main->to_print);
	return (actual_time);
}
