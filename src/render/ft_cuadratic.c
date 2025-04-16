/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cuadratic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:07:30 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:07:50 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

t_vec2	ft_cuadratic(double a, double b, double c)
{
	t_vec2	values;
	double	disc;
	double	tmp;

	disc = sqrt(pow(b, 2) - 4 * a * c);
	values.t0 = (-b - disc) / (2 * a);
	values.t1 = (-b + disc) / (2 * a);
	if (values.t0 > values.t1)
	{
		tmp = values.t0;
		values.t0 = values.t1;
		values.t1 = tmp;
	}
	return (values);
}
