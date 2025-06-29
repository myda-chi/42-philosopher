/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:59:27 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/29 12:38:51 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	create_philosophers(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
		pthread_create(&args->philos[i].thread, NULL, ph_routine,
			&args->philos[i]);
	return (true);
}

static bool	join_philosophers(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
		pthread_join(args->philos[i].thread, NULL);
	return (true);
}

static bool	destroy_forks(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
		pthread_mutex_destroy(&args->philos[i].l_fork);
	return (true);
}

static bool	monitor_simulation(t_args *args)
{
	int	i;

	i = -1;
	if (args->philo_count > 1)
	{
		while (1)
		{
			i++;
			if  (i >= args->philo_count)
				i = 0;
			if (ck_simulation_status(args, &i))
				break ;
			usleep(100);
		}
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_args	args;

	memset(&args, 0, sizeof(t_args));
	if (argc < 5 || argc > 6 || !ft_initialize_args(&args, argv))
		return (1);
	ft_initialize_philos(&args);
	create_philosophers(&args);
	monitor_simulation(&args);
	join_philosophers(&args);
	destroy_forks(&args);
	ft_cleanup(&args);
	return (0);
}
