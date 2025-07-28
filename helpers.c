/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/24 19:16:22 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

bool	ft_isint(char *str)
{
	char	*max_int;
	size_t	len;

	max_int = "2147483647";
	if (*str == '+')
		str++;
	len = ft_strlen(str);
	if (len > 10)
		return (false);
	if (len == 10)
		while (is_digit(*str) && *str <= *max_int++)
			str++;
	else
		while (is_digit(*str))
			str++;
	return (!*str && true);
}

void	ft_usleep(long time_ms)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < time_ms)
		usleep(500);
}
