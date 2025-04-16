/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:02 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:13:25 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

t_vec3	ft_difuse_light(t_light *light, t_hit *hit)
{
	t_vec3	light_dir;
	t_vec3	diffuse;
	double	intensity;
	double	gain;
	double	r2;

	light_dir = ft_sub(light->position, hit->point);
	r2 = ft_length_squared(light_dir);
	light_dir = ft_norm(light_dir);
	gain = ft_dot(light_dir, hit->normal);
	if (gain <= 0)
		intensity = 0.0;
	else
		intensity = (light->brightness * gain * 1000) / (4.0f * M_PI * r2);
	diffuse = ft_scale_color(hit->color, intensity);
	return (ft_adjust_color(diffuse, light->color));
}

int	ft_shadow(t_image *image, t_hit	*hit)
{
	t_ray	*shadow;
	int		touch;

	shadow = ft_calloc(sizeof(t_ray), 1);
	shadow->hit = ft_calloc(sizeof(t_hit), 1);
	shadow->origin = ft_add(hit->point, ft_scale(hit->normal, 0.001f));
	shadow->direction = ft_norm(
			ft_sub(image->objects->light->position, shadow->origin));
	shadow->hit->time = INFINITY;
	touch = ft_hit_anything(image, shadow);
	free(shadow->hit);
	free(shadow);
	return (touch);
}

t_vec3	ft_light_point(t_light *light, t_hit *hit, t_vec3 color)
{
	t_vec3	diffuse_light;
	t_vec3	result;

	diffuse_light = ft_difuse_light(light, hit);
	result = ft_add(diffuse_light, color);
	return (ft_clamp(result));
}
