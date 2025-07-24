/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:42 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/24 19:14:22 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_isint(av[i]) || ft_atoi(av[i]) <= 0)
			return (false);
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		return (false);
	return (true);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time_ms() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
