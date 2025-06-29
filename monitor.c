/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/29 12:38:10 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	handle_single_philo(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", ft_now_ms() - philo->args->start_time,
		philo->nbr);
	ft_usleep(philo->args->time2die, philo);
	return (false);
}

bool	handle_even_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_lock(&philo->l_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	return (true);
}

bool	handle_odd_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	return (true);
}

bool	pick_forks(t_philo *philo)
{
	if (philo->args->philo_count == 1)
		return (handle_single_philo(philo));
	if (should_stop(philo))
		return (false);
	if (philo->nbr % 2 == 0)
		return (handle_even_philo(philo));
	else
		return (handle_odd_philo(philo));
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
