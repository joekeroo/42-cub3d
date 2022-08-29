/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:13:17 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/08/18 11:23:49 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	size_t	long_max;
	size_t	num;
	int		sign;

	long_max = 9223372036854775807;
	num = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (is_num(*str))
	{
		num *= 10;
		num += *str++ - '0';
		if (num > long_max)
			return (-1 + (sign == -1));
	}
	return (num * sign);
}
