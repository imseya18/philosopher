/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:31:53 by seya              #+#    #+#             */
/*   Updated: 2023/06/14 15:56:36 by mmorue           ###   ########.fr       */
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
	unsigned int	last_time_eat;
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
	long int		actual_time;
	pthread_t		main_th;
	pthread_mutex_t	*clone_time;
	pthread_mutex_t	check_time_eat;
	pthread_mutex_t	to_print;
	pthread_mutex_t	alive;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
	struct timeval	start;
	struct timeval	end;
}	t_main;

typedef struct s_memng
{
	void			*mem;
	int				type;
	int				fd;
	struct s_memng	*next;
}	t_memng;

//CHECKER ROUTINE
void				*checker_routine(void *philippe);
int					check_number_eat(t_main *main);
int					check_time_dead(t_main *main);

//MAIN
int					init_mutex(t_main	*main);
int					init_philo(t_main	*main);
void				ft_destructor(t_main *main);
int					init_variable(char **argv, t_main *main);

//PHILO ROUTINE
void				*thread_routine(void *philippe);
int					check_if_dead(t_main *main);
void				philo_sleep_think(t_philo *philo, t_main *main);
void				philo_eating(t_philo *philo, t_main *main);
int					philo_fail(t_main *main, int i);

//TIME
unsigned int		time_for_usleep(void);
void				ft_usleep(int action_time, int eat, t_philo *philo);
void				ft_print_case(t_main *main, int cases, int eat_number,
						int philo_nb);
void				ft_print_case_two(t_main *main, int cases, int philo_nb);
void				get_time_print_action(t_main *main, int cases,
						t_philo *philo);

//UTILS
int					ft_atoi(const char *str);
int					check_if_digit(char *str);
void				add_time_they_eat(t_philo *philo, t_main *main);
int					destroy_mutex_problem(t_main *main, int i, int cases);

// MEMORY MANAGER
t_memng				**ft_head_lst(void);
t_memng				*ft_memnew_manager(void *mem, int type, int fd);
void				ft_memadd_back_manager(t_memng **lst, t_memng *new);
int					ft_is_in_lst(void *mem);
void				*ftm_malloc(size_t sz);
void				ftm_free(void *mem);
void				ftm_free_all(void);
void				ftm_add_track(void *mem);
void				ftm_rm_track(void *mem);
#endif