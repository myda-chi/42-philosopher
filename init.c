/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/29 12:36:05 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_initialize_args(t_args *args, char **argv)
{
	if (!error_handler(argv))
		return (false);
	args->philo_count = ft_atoi(argv[1]);
	args->time2die = ft_atoi(argv[2]);
	args->time2eat = ft_atoi(argv[3]);
	args->time2sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->max_meals = ft_atoi(argv[5]);
	else
		args->max_meals = -1;
	pthread_mutex_init(&args->sync_mutex, NULL);
	args->start_time = ft_now_ms();
	args->philos = malloc(sizeof(t_philo) * args->philo_count);
	if (!args->philos)
		return (false);
	return (true);
}

void	ft_initialize_philos(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
	{
		args->philos[i].nbr = i + 1;
		args->philos[i].last_meal_beginning = args->start_time;
		pthread_mutex_init(&args->philos[i].l_fork, NULL);
		if (i + 1 == args->philo_count)
			args->philos[i].r_fork = &args->philos[0].l_fork;
		else
			args->philos[i].r_fork = &args->philos[i + 1].l_fork;
		args->philos[i].args = args;
	}
}

void	ft_cleanup(t_args *args)
{
	if (args->philos)
	{
		free(args->philos);
		args->philos = NULL;
	}
	pthread_mutex_destroy(&args->sync_mutex);
}
