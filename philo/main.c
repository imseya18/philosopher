/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seya <seya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:30:29 by seya              #+#    #+#             */
/*   Updated: 2023/05/28 03:18:10 by seya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_digit(char *str)
{
	int i;

	i = 0;
	if(!str)
		return (0);
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

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

int	init_philo(char **argv, t_main *main)
{
	int i;

	i = 1;
	while(argv[i])
	{
		if (check_if_digit(argv[i]) == 0)
		{
			printf("error one of the argument isn't a digit\n");
			return (0);
		}
		i++;
	}
	main->nb_philo = atoi(argv[1]);
	main->to_die = atoi(argv[2]);
	main->to_eat = atoi(argv[3]);
	main->to_sleep = atoi(argv[4]);
	if (argv[5])
		main->number_eat = atoi(argv[5]);
	else
		main->number_eat = 0;
	return (1);
}
long int	get_time(t_main *s_main)
{
	long int 	end_time;
	long int	actual_time;
	
	actual_time = 0;
	end_time = 0;
	gettimeofday(&(s_main->end), NULL);
	end_time = (s_main->end.tv_sec * 1000 + s_main->end.tv_usec / 1000);
	actual_time = (end_time - s_main->start_time);
	//printf("Time taken to count to 10^5 is : %ld ms\n", (end_time - s_main->start_time));
	return (actual_time);
}
int main(int argc, char **argv)
{
	t_main s_main;

	if (argc != 5 && argc != 6)
	{
		printf("wrong number of arg \n");
		return (0);
	}
	else
	{
		if (init_philo(argv, &s_main) == 0)
			return (0);
		gettimeofday(&(s_main.start), NULL);
		s_main.start_time = (s_main.start.tv_sec * 1000 + s_main.start.tv_usec / 1000);
		while(1)
		{
			printf("%ld\n",get_time(&s_main));
		}
		return 0;
	}
}