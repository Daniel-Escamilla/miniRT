/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:53:45 by descamil          #+#    #+#             */
/*   Updated: 2025/04/16 12:11:14 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

double	ft_dot(t_vec3 a, t_vec3 b)
{
	double	result;

	result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (result);
}

t_vec3	ft_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	
	return (result);
}

double	ft_length_squared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3	ft_norm(t_vec3 v)
{
	return (ft_scale(v, 1 / sqrt(ft_length_squared(v))));
}
