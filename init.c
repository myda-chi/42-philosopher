/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/28 19:37:32 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool init_forks(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->forks)
        return (false);
    i = 0;
    while (i < data->nb_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (false);
        i++;
    }
    return (true);
}

static bool init_philos(t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * data->nb_philo);
    if (!data->philos)
        return (false);
    i = 0;
    while (i < data->nb_philo)
    {
        data->philos[i].id = i + 1;
        data->philos[i].l_fork = &data->forks[i];
        data->philos[i].r_fork = &data->forks[(i + 1) % data->nb_philo];
        data->philos[i].last_meal = data->start_time;
        data->philos[i].meals_eaten = 0;
        data->philos[i].data = data;
        i++;
    }
    return (true);
}

bool    init_data(t_data *data, int ac, char **av)
{
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->nb_meals = -1;
    if (ac == 6)
        data->nb_meals = ft_atoi(av[5]);
    data->someone_died = 0;
    data->start_time = get_time_ms();
    if (!init_forks(data))
        return (false);
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0
        || pthread_mutex_init(&data->death_mutex, NULL) != 0)
        return (false);
    if (!init_philos(data))
        return (false);
    return (true);
}