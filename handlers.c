/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:42 by myda-chi          #+#    #+#             */
/*   Updated: 2025/08/03 16:04:09 by myda-chi         ###   ########.fr       */
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

void print_status(t_philo *philo, const char *msg)
{
    pthread_mutex_lock(&philo->data->death_mutex);
    int dead = philo->data->someone_died;
    pthread_mutex_unlock(&philo->data->death_mutex);
    if (!dead)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        long now = get_time_ms() - philo->data->start_time;
        printf("%ld %d %s\n", now, philo->id, msg);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
}

void print_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    long now = get_time_ms() - philo->data->start_time;
    printf("\033[0;31m%ld %d died\033[0m\n", now, philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
