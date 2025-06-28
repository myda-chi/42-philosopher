/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:44:53 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/28 19:38:56 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
#include <stdlib.h>

typedef struct s_philo
{
    int                 id;
    pthread_t           philo;
    pthread_mutex_t     *l_fork;
    pthread_mutex_t     *r_fork;
    long                last_meal;
    int                 meals_eaten;
    struct s_data       *data;
}   t_philo;

typedef struct s_data
{
    int                 nb_philo;
    int                 time_to_die;
    int                 time_to_eat;
    int                 time_to_sleep;
    int                 nb_meals;
    pthread_mutex_t     *forks;
    pthread_mutex_t     print_mutex;
    pthread_mutex_t     death_mutex;
    long                start_time;
    int                 someone_died;
    t_philo             *philos;
    pthread_t           monitor;
}   t_data;

// utils.c
long    get_time_ms(void);
int     ft_atoi(const char *str);
size_t  ft_strlen(char *str);
int     is_digit(char c);
bool    ft_isint(char *str);

// init.c
bool    init_data(t_data *data, int ac, char **av);

// routine.c
void    print_status(t_philo *philo, char *status);
void    eat(t_philo *philo);
void    *philo_routine(void *arg);

// monitor.c
bool    check_death(t_data *data);
bool    check_meals(t_data *data);
void    *monitor_routine(void *arg);

// handlers.c
bool    check_args(char **av);

#endif