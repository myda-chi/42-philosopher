/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/28 19:48:13 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d %s\n", get_time_ms() - philo->data->start_time,
        philo->id, status);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

static void    take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->r_fork);
        print_status(philo, "has taken a fork");
    }
}

static void    release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void    eat(t_philo *philo)
{
    take_forks(philo);
    print_status(philo, "is eating");
    philo->last_meal = get_time_ms();
    usleep(philo->data->time_to_eat * 1000);
    philo->meals_eaten++;
    release_forks(philo);
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->someone_died)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            break ;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);
        eat(philo);
        print_status(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        print_status(philo, "is thinking");
    }
    return (NULL);
}