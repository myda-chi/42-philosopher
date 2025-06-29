/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:42 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/29 12:34:57 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	error_handler(char **av)
{
	if (ft_atoi(av[1]) <= 0 || !ft_isint(av[1]))
	{
		write(2, "Invalid number of philosopher\n", 30);
		return (false);
	}
	if (ft_atoi(av[2]) <= 0 || !ft_isint(av[2]))
	{
		write(2, "Invalid time to die\n", 21);
		return (false);
	}
	if (ft_atoi(av[3]) <= 0 || !ft_isint(av[3]))
	{
		write(2, "Invalid time to eat\n", 21);
		return (false);
	}
	if (ft_atoi(av[4]) <= 0 || !ft_isint(av[4]))
	{
		write(2, "Invalid time to sleep\n", 23);
		return (false);
	}
	if (av[5] && (ft_atoi(av[5]) <= 0 || !ft_isint(av[5])))
	{
		write(2, "Invalid number of time philosopher must eat\n", 44);
		return (false);
	}
	return (true);
}

time_t	ft_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL);
}

void	ft_usleep(time_t milli, t_philo *philo)
{
	time_t	now;
	time_t	elapsed;

	now = ft_now_ms();
	elapsed = ft_now_ms();
	while (elapsed - now < milli)
	{
		if (should_stop(philo))
			return ;
		usleep(300);
		elapsed = ft_now_ms();
	}
}
