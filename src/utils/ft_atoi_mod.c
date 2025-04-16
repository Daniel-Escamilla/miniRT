/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:34:57 by descamil          #+#    #+#             */
/*   Updated: 2025/04/16 12:46:43 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static int	handle_sign(char *str, int *i, int *sign)
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

int	calculate_result(char *str, int *i, int *error, int sign)
{
	long long	result;
	int			digit;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (sign == 1 && (result > (INT_MAX / 10)
				|| (result == (INT_MAX / 10) && digit > 7)))
		{
			*error = 2;
			return (INT_MAX);
		}
		if (sign == -1 && (result > (INT_MAX / 10)
				|| (result == (INT_MAX / 10) && digit > 8)))
		{
			*error = 2;
			return (INT_MIN);
		}
		result = result * 10 + digit;
		(*i)++;
	}
	return ((int)result);
}

int	ft_atoi_mod(char *str, int *error)
{
	int			result;
	int			sign;
	int			i;

	i = 0;
	sign = 1;
	*error = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (handle_sign(str, &i, &sign) && (str[i] == '-' || str[i] == '+'
			|| !(str[i] >= '0' && str[i] <= '9')))
	{
		*error = 3;
		return (0);
	}
	result = calculate_result(str, &i, error, sign);
	return (result * sign);
}
