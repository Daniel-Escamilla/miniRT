/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:03:32 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:11:34 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

t_vec3	ft_vec3(double a, double b, double c)
{
	t_vec3	result;

	result.x = a;
	result.y = b;
	result.z = c;
	return (result);
}

double	ft_len_sqr(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	ft_len(t_vec3 v)
{
	return (sqrt(ft_len_sqr(v)));
}

t_vec3	ft_float_to_vec3(double a)
{
	t_vec3	result;

	result.x = a;
	result.y = a;
	result.z = a;
	return (result);
}
