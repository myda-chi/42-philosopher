/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:44:53 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/29 12:33:17 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				nbr;
	time_t			last_meal_beginning;
	int				meals_count;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_args	*args;
}					t_philo;

typedef struct s_args
{
	int				philo_count;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				max_meals;
	int				total_finished;
	bool			someone_died;
	bool			all_full;
	time_t			start_time;
	pthread_mutex_t	sync_mutex;
	struct s_philo	*philos;
}					t_args;

enum				e_fork
{
	LEFT,
	RIGHT
};

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
bool				ft_isint(char *str);
bool				error_handler(char **av);
time_t				ft_now_ms(void);
size_t				ft_strlen(const char *str);
void				ft_usleep(time_t milli, t_philo *philo);
bool				ft_initialize_args(t_args *args, char **argv);
void				ft_initialize_philos(t_args *args);
void				ft_cleanup(t_args *args);
bool				ft_write_status(t_philo *philo, char *msg);
bool				ck_simulation_status(t_args *args, int *i);
bool				should_stop(t_philo *philo);
bool				pick_forks(t_philo *philo);
void				ft_eat(t_philo *philo);
bool				sleep_then_think(t_philo *philo);
void				release_forks(t_philo *philo);
void				*ph_routine(void *data);

#endif