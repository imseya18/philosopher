/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:15:19 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/14 15:56:45 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	calcul(const char *str, int i, int k)
{	
	int	res;

	res = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (k == 1)
		res = -res;
	return (res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	j = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k++;
		if (str[i] == '+')
			j++;
		i++;
	}
	if (j > 1 || k > 1 || (k + j) > 1)
		return (0);
	return (calcul(str, i, k));
}

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

void	add_time_they_eat(t_philo *philo, t_main *main)
{
	pthread_mutex_lock(&main->check_time_eat);
	philo->eat_number++;
	pthread_mutex_unlock(&main->check_time_eat);
}

int	destroy_mutex_problem(t_main *main, int i, int cases)
{
	int	k;

	k = -1;
	if (cases <= 4)
		pthread_mutex_destroy(&main->to_print);
	if (cases >= 2 && cases <= 4)
		pthread_mutex_destroy(&main->alive);
	if (cases == 3)
	{
		pthread_mutex_destroy(&main->check_time_eat);
		while (++k < i)
			pthread_mutex_destroy(&main->fork[k]);
	}
	if (cases == 4)
	{
		pthread_mutex_destroy(&main->check_time_eat);
		while (++k < main->nb_philo)
			pthread_mutex_destroy(&main->fork[k]);
		k = -1;
		while (++k < i)
			pthread_mutex_destroy(&main->clone_time[i]);
	}
	return (1);
}
