/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:44:53 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/24 19:15:30 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread_id;
	long			last_meal;
	int				id;
	int				l_fork;
	int				r_fork;
	int				meals_eaten;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*fork_mutexes;
	int				*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	long			start_time;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				someone_died;
}					t_data;

// utils.c
long				get_time_ms(void);
int					ft_atoi(const char *str);
size_t				ft_strlen(char *str);
int					is_digit(char c);
bool				ft_isint(char *str);
void				ft_usleep(long time_ms);

// init.c
bool				init_data(t_data *data, int ac, char **av);
void				cleanup_data(t_data *data);

// routine.c
void				print_status(t_philo *philo, char *status);
void				eat(t_philo *philo);
void				*philo_routine(void *arg);

// monitor.c
bool				check_death(t_data *data);
bool				check_meals(t_data *data);
void				*monitor_routine(void *arg);

// handlers.c
bool				check_args(char **av);

#endif