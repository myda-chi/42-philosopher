/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/24 19:13:10 by myda-chi         ###   ########.fr       */
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
		if (current_time - data->philos[i].last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("\033[0;31m %ld%ddied\033[0m\n", current_time
				- data->start_time, data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (true);
		}
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
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten < data->nb_meals)
			return (false);
		i++;
	}
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
