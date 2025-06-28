/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:42 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/28 19:37:41 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool check_args(char **av)
{
    if (ft_atoi(av[1]) <= 0 || !ft_isint(av[1]))
    {
        write(2, "Invalid number of philosopher\n", 30);
        return false;
    }
    if (ft_atoi(av[2]) <= 0 || !ft_isint(av[2]))
    {
        write(2, "Invalid time to die\n", 21);
        return false;
    }
    if (ft_atoi(av[3]) <= 0 || !ft_isint(av[3]))
    {
        write(2, "Invalid time to eat\n", 21);
        return false;
    }
    if (ft_atoi(av[4]) <= 0 || !ft_isint(av[4]))
    {
        write(2, "Invalid time to sleep\n", 23);
        return false;
    }
    if (av[5] && (ft_atoi(av[5]) <= 0 || !ft_isint(av[5])))
    {
        write(2, "Invalid number of time philosopher must eat\n", 44);
        return false;
    }
    return true;
}
