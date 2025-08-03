/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:59:27 by myda-chi          #+#    #+#             */
/*   Updated: 2025/08/03 16:02:57 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
		return (false);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: %s nb_philo time_to_die time_to_eat time_to_sleep\n",
			av[0]);
		return (1);
	}
	if (!check_args(av))
		return (printf("Error: Invalid arguments\n"), 1);
	if (!init_data(&data, ac, av))
		return (printf("Error: Initialization failed\n"), 1);
	if (data.nb_philo == 1)
	{
		printf("\033[0;33mhas taken a fork\033[0m\n");
		ft_usleep(data.time_to_die);
		printf("\033[0;31m%d 1 died\033[0m\n", data.time_to_die);
		cleanup_data(&data);
		return (0);
	}
	if (!start_simulation(&data))
		return (printf("Error: Simulation failed\n"), cleanup_data(&data), 1);
	cleanup_data(&data);
	return (0);
}
