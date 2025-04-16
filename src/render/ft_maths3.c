/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:10:36 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:11:48 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

t_vec3	ft_clamp(t_vec3 color)
{
	if (color.x < 0.0f)
		color.x = 0.0f;
	else if (color.x > 1.0f)
		color.x = 1.0f;
	if (color.y < 0.0f)
		color.y = 0.0f;
	else if (color.y > 1.0f)
		color.y = 1.0f;
	if (color.z < 0.0f)
		color.z = 0.0f;
	else if (color.z > 1.0f)
		color.z = 1.0f;
	return (color);
}

t_vec3	ft_normalice(t_vec3 vec)
{
	double	magnitud;

	magnitud = ft_dot(vec, vec);
	magnitud = sqrt(magnitud);
	if (magnitud == 0.0f)
		return (vec);
	vec.x /= magnitud;
	vec.y /= magnitud;
	vec.z /= magnitud;
	return (vec);
}

t_vec3	ft_scale(t_vec3 value, double scale)
{
	t_vec3	result;

	result.x = scale * value.x;
	result.y = scale * value.y;
	result.z = scale * value.z;
	return (result);
}
