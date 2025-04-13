/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:53:45 by descamil          #+#    #+#             */
/*   Updated: 2025/04/09 19:33:56 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

double	ft_dot(t_vec3 a, t_vec3 b)
{
	double result;

	result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

	return (result);
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

t_vec3	ft_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result);
}

t_vec3	ft_vec3(double a, double b, double c)
{
	t_vec3	result;

	result.x = a;
	result.y = b;
	result.z = c;
	return (result);
}
