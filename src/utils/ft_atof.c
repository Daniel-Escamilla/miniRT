/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:37:03 by descamil          #+#    #+#             */
/*   Updated: 2024/11/03 12:40:14 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static float	ft_deci(float nb, char *str, int i)
{
	float	deci;

	deci = 0.1;
	if (str[i] == '-' && ++i > 0)
		return (3);
	while (ft_isdigit(str[++i]) == 1)
	{
		nb = nb + (str[i] - '0') * deci;
		deci *= 0.1;
	}
	return (nb);
}

float	ft_atof(char *str)
{
	int		i;
	int		m;
	float	nb;

	i = 0;
	m = 1;
	nb = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '.')
		return (0);
	if (str[i] == '-' && ++i > 0)
		m = -1;
	while (ft_isdigit(str[i]) == 1)
		nb = nb * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
		nb = ft_deci(nb, str, i);
	return (nb * m);
}
