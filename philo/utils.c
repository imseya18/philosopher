/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:15:19 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/06 15:35:52 by mmorue           ###   ########.fr       */
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
