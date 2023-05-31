/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:31:53 by seya              #+#    #+#             */
/*   Updated: 2023/05/31 17:46:34 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				philo_nb;
	pthread_t		philo_th;
	struct	s_main	*main;
}	t_philo;


typedef	struct s_fork
{
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_main
{
	int				nb_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				number_eat;
	int				actual_philo;
	int				test;
	long int		start_time;
	pthread_mutex_t	*fork;
	struct timeval	start;
	struct timeval	end;
}	t_main;

int			init_variable(char **argv, t_main *main);
long int	get_time(t_main *s_main, int cases, int philo_nb);
int			ft_atoi(const char *str);
int			check_if_digit(char *str);
void		init_philo(t_philo *philo, t_main	*main);
void		*thread_routine(void *philippe);

#endif