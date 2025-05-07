/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:00:38 by descamil          #+#    #+#             */
/*   Updated: 2025/05/07 12:00:46 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_sign(const char *str, int *i, int *sign)
{
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	else
		return (0);
	return (1);
}

static int	calculate_result(const char *str, int *i, int sign)
{
	long long	result;
	int			digit;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (sign == 1 && (result > (INT_MAX / 10)
				|| (result == (INT_MAX / 10) && digit > 7)))
			return (INT_MAX);
		else if (sign == -1 && (result > (INT_MAX / 10)
				|| (result == (INT_MAX / 10) && digit > 8)))
			return (INT_MIN);
		result = result * 10 + digit;
		(*i)++;
	}
	return ((int)result);
}

int	ft_atoi(const char *str)
{
	int			result;
	int			sign;
	int			i;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (handle_sign(str, &i, &sign) && (str[i] == '-' || str[i] == '+'
			|| !(str[i] >= '0' && str[i] <= '9')))
		return (0);
	if ((sign == 0 && ft_strlen(str) > 10)
		|| (sign == 1 && ft_strlen(str) > 11))
		return (0);
	result = calculate_result(str, &i, sign);
	if (str[i] != '\0')
		return (0);
	return (result * sign);
}
