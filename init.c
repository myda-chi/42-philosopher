/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/08/03 16:03:14 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_forks(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork_mutexes)
		return (false);
	data->forks = malloc(sizeof(int) * data->nb_philo);
	if (!data->forks)
		return (false);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork_mutexes[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

static bool	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (false);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->nb_philo;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

void	cleanup_data(t_data *data)
{
	int	i;

	if (data->fork_mutexes)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->fork_mutexes[i]);
			i++;
		}
		free(data->fork_mutexes);
		data->fork_mutexes = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}

bool	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nb_meals = -1;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	data->start_time = get_time_ms();
	data->someone_died = 0;
	data->fork_mutexes = NULL;
	data->forks = NULL;
	data->philos = NULL;
	if (!init_forks(data))
	{
		cleanup_data(data);
		return (false);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->death_mutex, NULL) != 0
		|| pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		return (cleanup_data(data), false);
	}
	if (!init_philos(data))
		return (cleanup_data(data), false);
	return (true);
}
