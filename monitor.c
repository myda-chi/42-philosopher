/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/28 20:06:49 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool check_philo_death(t_data *data, int i)
{
    long    time_since_meal;

    time_since_meal = get_time_ms() - data->philos[i].last_meal;
    if (time_since_meal > data->time_to_die)
    {
        print_status(&data->philos[i], "died");
        data->someone_died = 1;
        return (true);
    }
    return (false);
}

bool    check_death(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_lock(&data->death_mutex);
        if (check_philo_death(data, i))
        {
            pthread_mutex_unlock(&data->death_mutex);
            return (true);
        }
        pthread_mutex_unlock(&data->death_mutex);
        i++;
    }
    return (false);
}

bool    check_meals(t_data *data)
{
    int i;

    if (data->nb_meals == -1)
        return (false);
    i = 0;
    while (i < data->nb_philo)
    {
        if (data->philos[i].meals_eaten < data->nb_meals)
            return (false);
        i++;
    }
    return (true);
}

void    *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < data->nb_philo)
        {
            pthread_mutex_lock(&data->death_mutex);
            if (get_time_ms() - data->philos[i].last_meal > data->time_to_die)
            {
                data->someone_died = 1;
                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d died\n", get_time_ms() - data->start_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);
                pthread_mutex_unlock(&data->death_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->death_mutex);
            i++;
        }
        usleep(1000); // check every 1ms
    }
    return NULL;
}