/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_per_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:29:21 by descamil          #+#    #+#             */
/*   Updated: 2025/04/16 12:23:34 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

t_ray	*ft_init_ray(t_image *image, t_vec2 coord)
{
	t_camera	*camera;
	t_vec3		horizontal_scaled;
	t_vec3		vertical_scaled;
	t_ray		*ray;

	camera = image->objects->camera;
	ray = ft_calloc(sizeof(t_ray), 1);
	ray->hit = ft_calloc(sizeof(t_hit), 1);
	horizontal_scaled = ft_mult(camera->horizontal,
			ft_float_to_vec3(coord.x));
	vertical_scaled = ft_mult(camera->vertical,
			ft_float_to_vec3(coord.y));
	ray->origin = camera->position;
	ray->direction = ft_add(horizontal_scaled, vertical_scaled);
	ray->direction = ft_add(ray->direction, camera->l_left_corner);
	ray->direction = ft_normalice(ft_sub(ray->direction, ray->origin));
	return (ray);
}

int	ft_hit_anything(t_image *image, t_ray *ray)
{
	bool		hit;
	t_sphere	*current_sphere;
	t_plane		*current_plane;
	t_cylinder	*current_cylinder;

	hit = false;
	current_sphere = image->objects->sphere;
	while (current_sphere)
	{
		ft_hit_sphere(current_sphere, ray, &hit);
		current_sphere = current_sphere->next;
	}
	current_plane = image->objects->plane;
	while (current_plane)
	{
		ft_hit_plane(current_plane, ray, &hit);
		current_plane = current_plane->next;
	}
	current_cylinder = image->objects->cylinder;
	while (current_cylinder)
	{
		ft_hit_cylinder(current_cylinder, ray, &hit);
		current_cylinder = current_cylinder->next;
	}
	return (hit);
}

t_vec3	ft_per_pixel(t_image *image, t_vec2 coord)
{
	t_image	*current;
	t_vec3	ambient_color;
	t_vec3	color;
	t_ray	*ray;

	color = (t_vec3){{0.0f, 0.0f, 0.0f}};
	ray = ft_init_ray(image, coord);
	current = image;
	ray->hit->time = INFINITY;
	if (ft_hit_anything(current, ray) == 0)
	{
		free(ray->hit);
		free(ray);
		return ((t_vec3){{0.0f, 0.0f, 0.0f}});
	}
	current = image;
	ambient_color = ft_scale_color(current->objects->ambient->color,
			current->objects->ambient->ambient_light);
	color = ft_adjust_color(ray->hit->color, ambient_color);
	if (!ft_shadow(current, ray->hit))
		color = ft_light_point(current->objects->light, ray->hit, color);
	free(ray->hit);
	free(ray);
	return (color);
}
