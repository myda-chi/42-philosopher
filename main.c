/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:59:27 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/28 19:38:22 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void cleanup(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
    free(data->forks);
    free(data->philos);
}

int main(int ac, char **av)
{
    t_data  data;
    int     i;

    if (ac < 5 || ac > 6)
    {
        printf("Usage: %s nb_philo time_to_die time_to_eat time_to_sleep "
            "[nb_meals]\n", av[0]);
        return (1);
    }
    if (!check_args(av))
        return (1);
    if (!init_data(&data, ac, av))
        return (1);
    i = 0;
    while (i < data.nb_philo)
    {
        pthread_create(&data.philos[i].philo, NULL, philo_routine,
            &data.philos[i]);
        i++;
    }
    pthread_create(&data.monitor, NULL, monitor_routine, &data);
    i = 0;
    while (i < data.nb_philo)
    {
        pthread_join(data.philos[i].philo, NULL);
        i++;
    }
    pthread_join(data.monitor, NULL);
    cleanup(&data);
    return (0);
}
