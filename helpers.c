/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:06:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/06/29 12:37:58 by myda-chi         ###   ########.fr       */
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

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
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
		while (ft_isdigit(*str) && *str <= *max_int++)
			str++;
	else
		while (ft_isdigit(*str))
			str++;
	return (!*str && true);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
