/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:59:41 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/01 16:54:36 by mmorue           ###   ########.fr       */
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