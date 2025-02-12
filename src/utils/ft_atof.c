/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:37:03 by descamil          #+#    #+#             */
/*   Updated: 2025/02/10 19:12:54 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	handle_sign(char *str, int *i, int *error)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i + 1] == '-' || str[*i + 1] == '+')
		{
			*error = -1;
			return (-1);
		}
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
		if (str[*i] == '\0')
			*error = -1;
	}
	return (sign);
}

double	convert_integer_part(char *str, int *i, int *error)
{
	int			start;
	double	nb;
	int			n;

	nb = 0.0f;
	start = *i;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		n = (str[*i] - '0');
		nb *= 10;
		nb += n;
		(*i)++;
		if (*i - start > 39)
			*error = -1;
	}
	return (nb);
}

double	convert_decimal_part(char *str, int *i, int *error)
{
	double	decimal_div;
	double	nb;

	nb = 0.0f;
	decimal_div = 10.0f;
	if (str[*i] == '.' && ft_isdigit(str[*i - 1]) == 0)
		*error = -1;
	if (str[(*i)++] == '.' && *error != -1)
	{
		while (str[*i] != '\0' && *error != -1)
		{
			if (ft_isdigit(str[*i]) == 0)
				*error = -1;
			nb += (str[*i] - '0') / (decimal_div);
			decimal_div *= 10.0f;
			(*i)++;
		}
	}
	return (nb);
}

int	ft_all_numbers(char *str)
{
	int	point;
	int	i;

	i = 0;
	point = 0;
	while (str && str[i] == ' ')
		i++;
	if (str && str[i] == '-')
		i++;
	while (str && (ft_isdigit(str[i]) || (str[i] == '.' && point != 1)))
	{
		if (str[i] == '.')
			point = 1;
		i++;
	}
	while (str && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

double	ft_atof(char *str)
{
	int		error;
	double	sign;
	double	nb;
	int		i;

	i = 0;
	sign = 1;
	error = 0;
	if (ft_all_numbers(str) == 1)
		return (-0.0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-0.0f);
	sign = handle_sign(str, &i, &error);
	nb = convert_integer_part(str, &i, &error);
	if (error == -1)
		return (-0.0f);
	if (str[i] == '.')
		nb += convert_decimal_part(str, &i, &error);
	if (error == -1)
		return (-0.0f);
	if (nb == 0.0f)
		sign = 1;
	return ((double)sign * (double)nb);
}

// int	main(void)
// {
// 	printf("%f\n", ft_atof("340282346638528859811704183484516925440"));
// 	printf("%f\n", atof("340282346638528859811704183484516925440"));
// 	// printf(B_PR_0"%f\n"RESET, atof("2147483645"));
// 	// printf(B_GR_0"-> %lf\n"RESET, ft_atof("214783645"));
// 	return (0);
// }
