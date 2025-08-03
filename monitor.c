/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/08/03 16:02:01 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_data *data)
{
	int		i;
	long	current_time;

	i = 0;
	current_time = get_time_ms();
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (current_time - data->philos[i].last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			print_death(&data->philos[i]);
			return (true);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (false);
}

bool	check_meals(t_data *data)
{
	int	i;

	if (data->nb_meals == -1)
		return (false);
	i = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten < data->nb_meals)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_meals(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
