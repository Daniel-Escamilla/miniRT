/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_per_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:29:21 by descamil          #+#    #+#             */
/*   Updated: 2025/04/05 13:39:06 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

t_ray ft_init_ray(t_image *image, t_vec2 coord)
{
    t_ray ray;
    t_camera *camera = image->objects->camera;

    t_vec3 horizontal_scaled = ft_multiply(camera->horizontal, ft_float_to_vec3(coord.x));
    t_vec3 vertical_scaled = ft_multiply(camera->vertical, ft_float_to_vec3(coord.y));
    ray.origin = camera->position;
    ray.direction = ft_add(horizontal_scaled, vertical_scaled);
    ray.direction = ft_add(ray.direction, camera->l_left_corner);
    ray.direction = ft_normalice(ft_subtract(ray.direction, ray.origin));
    return (ray);
}


t_vec3	ft_per_pixel(t_image *image, t_vec2 coord)
{
	t_image	*current;
	t_ray	ray;

	ray = ft_init_ray(image, coord);
	current = image;
	if (current->objects->sphere)
	{
		ft_render_sphere(current, coord);
		current->objects->sphere = current->objects->sphere->next;
	}
	return ((t_vec3){{1.0f, 0.0f, 0.5f}});
}
