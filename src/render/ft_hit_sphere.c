/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:06:17 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:06:54 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	ft_hit_sphere(t_sphere *sphere, t_ray *ray, bool *hit)
{
	t_vec3	values;
	t_vec3	test;
	t_vec2	tt;

	test = ft_sub(ray->origin, sphere->position);
	values._a = ft_dot(ray->direction, ray->direction);
	values._b = 2.0f * ft_dot(test, ray->direction);
	values._c = ft_dot(test, test) - (sphere->radius * sphere->radius);
	tt = ft_cuadratic(values._a, values._b, values._c);
	if (tt.t0 < ray->hit->time && tt.t0 > 0)
	{
		ray->hit->time = tt.t0;
		ray->hit->point = ft_add(ray->origin,
				ft_mult(ray->direction, ft_float_to_vec3(tt.t0)));
		ray->hit->normal = ft_normalice(ft_sub(ray->hit->point,
					sphere->position));
		ray->hit->color = sphere->color;
		*hit = true;
	}
}
