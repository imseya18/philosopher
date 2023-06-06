/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:31:53 by seya              #+#    #+#             */
/*   Updated: 2023/06/06 16:25:45 by mmorue           ###   ########.fr       */
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
	long int		last_time_eat;
	int				eat_number;
	pthread_t		philo_th;
	struct s_main	*main;
}	t_philo;

typedef struct s_main
{
	int				nb_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				stop;
	int				number_eat;
	long int		start_time;
	pthread_mutex_t	check_time_eat;
	pthread_mutex_t	to_print;
	pthread_mutex_t	check_alive;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
	struct timeval	start;
	struct timeval	end;
}	t_main;

int					init_variable(char **argv, t_main *main);
int					ft_atoi(const char *str);
int					check_if_digit(char *str);
void				init_philo(t_main	*main);
void				*thread_routine(void *philippe);
void				philo_sleep_think(t_philo *philo, t_main *main);
void				philo_eating(t_philo *philo, t_main *main);
int					check_number_eat(t_main *main);
//	TIME
long int			get_time_print_action(t_main *s_main, int cases, int philo_nb, int fork_number);
unsigned int		time_for_usleep(void);
void				ft_usleep(int end_time);
#endif