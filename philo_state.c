/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:35:03 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/29 12:35:43 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->sync_mutex);
	if (philo->args->someone_died || philo->args->all_full)
	{
		pthread_mutex_unlock(&philo->args->sync_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->args->sync_mutex);
	return (false);
}

bool	ft_write_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->args->sync_mutex);
	if (philo->args->someone_died || philo->args->all_full)
	{
		pthread_mutex_unlock(&philo->args->sync_mutex);
		return (false);
	}
	printf("%ld %d %s\n", ft_now_ms() - philo->args->start_time, philo->nbr,
		msg);
	pthread_mutex_unlock(&philo->args->sync_mutex);
	return (true);
}

bool	ck_simulation_status(t_args *args, int *i)
{
	pthread_mutex_lock(&args->sync_mutex);
	if (ft_now_ms()
		- args->philos[*i].last_meal_beginning >= (time_t)args->time2die
		|| args->total_finished == args->philo_count)
	{
		if (args->max_meals != -1 && args->total_finished == args->philo_count)
		{
			args->all_full = true;
			printf("Every philosopher had a minimum of %d times\n",
				args->max_meals);
		}
		else
		{
			args->someone_died = true;
			printf("%ld %d died\n", ft_now_ms() - args->start_time,
				args->philos[*i].nbr);
		}
		pthread_mutex_unlock(&args->sync_mutex);
		return (true);
	}
	if (*i + 1 == args->philo_count)
		*i = -1;
	pthread_mutex_unlock(&args->sync_mutex);
	return (false);
}
