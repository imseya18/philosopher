/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:59:41 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/06 15:35:51 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int time_for_usleep()
{
	struct timeval time;
	unsigned int time_return;

	gettimeofday(&time, NULL);
	time_return = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time_return);
}

void ft_usleep(int end_time)
{
	unsigned int start_time;

	start_time = time_for_usleep();
	while(time_for_usleep() - start_time < (unsigned int)end_time)
		usleep(200);
}

long int	get_time_print_action(t_main *s_main, int cases, int philo_nb, int fork_number)
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
		printf("%ld %d has taken a fork %d\n", actual_time, (philo_nb + 1), (fork_number + 1));
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
