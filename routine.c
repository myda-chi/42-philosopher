/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/24 19:16:10 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->fork_mutexes[philo->r_fork]);
		print_status(philo, "\033[0;33mhas taken a fork\033[0m\n");
		pthread_mutex_lock(&philo->data->fork_mutexes[philo->l_fork]);
		print_status(philo, "\033[0;33mhas taken a fork\033[0m\n");
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork_mutexes[philo->l_fork]);
		print_status(philo, "\033[0;33mhas taken a fork\033[0m\n");
		pthread_mutex_lock(&philo->data->fork_mutexes[philo->r_fork]);
		print_status(philo, "\033[0;33mhas taken a fork\033[0m\n");
	}
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork_mutexes[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->fork_mutexes[philo->r_fork]);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, "\033[0;32mis eating 🍽️ 😋\033[0m");
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
	drop_forks(philo);
}

static bool	should_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (should_continue(philo))
	{
		eat(philo);
		if (!should_continue(philo))
			break ;
		print_status(philo, "\033[0;34mis sleeping 😴\033[0m");
		ft_usleep(philo->data->time_to_sleep);
		if (!should_continue(philo))
			break ;
		print_status(philo, "\033[0;34mis thinking 🧠🤔\033[0m");
	}
	return (NULL);
}
