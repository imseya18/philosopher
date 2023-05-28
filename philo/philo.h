/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seya <seya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:31:53 by seya              #+#    #+#             */
/*   Updated: 2023/05/28 03:18:12 by seya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_main
{
	int	nb_philo;
	int	to_die;
	int to_eat;
	int	to_sleep;
	int	number_eat;
	long int start_time;
	struct timeval start;
	struct timeval end;
	
} t_main;

#endif