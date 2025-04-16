/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:05:38 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:08:55 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	ft_hit_plane(t_plane *plane, t_ray *ray, bool *hit)
{
	double	test;
	double	tt;

	test = ft_dot(ft_norm(ray->direction), plane->normal);
	if (test >= 0.0)
		return ;
	tt = ft_dot(ft_sub(plane->position, ray->origin),
			plane->normal) / test;
	if (tt < ray->hit->time && tt > 0.0001)
	{
		ray->hit->time = tt;
		ray->hit->point = ft_add(ray->origin,
				ft_scale(ray->direction, ray->hit->time));
		ray->hit->normal = plane->normal;
		ray->hit->color = plane->color;
		*hit = true;
	}
}
