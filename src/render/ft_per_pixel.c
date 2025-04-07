/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_per_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:29:21 by descamil          #+#    #+#             */
/*   Updated: 2025/04/07 22:25:40 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

t_ray ft_init_ray(t_image *image, t_vec2 coord)
{
	t_camera	*camera = image->objects->camera;
	t_vec3		horizontal_scaled;
	t_vec3		vertical_scaled;
    t_ray		ray;

	horizontal_scaled = ft_multiply(camera->horizontal, ft_float_to_vec3(coord.x));
	vertical_scaled = ft_multiply(camera->vertical, ft_float_to_vec3(coord.y));
    ray.origin = camera->position;
    ray.direction = ft_add(horizontal_scaled, vertical_scaled);
    ray.direction = ft_add(ray.direction, camera->l_left_corner);
    ray.direction = ft_normalice(ft_subtract(ray.direction, ray.origin));
	ray.hit.time = INFINITY;
    return (ray);
}

t_vec2	ft_cuadratic(float a, float b, float c)
{
	t_vec2	values;
	float	disc;
	float	tmp;

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

void	ft_hit_sphere(t_image *image, t_ray ray, bool *hit)
{
	t_sphere	*sphere;
	t_vec3		values;
	t_vec3		test;
	t_vec2		tt;

	sphere = image->objects->sphere;
	test = ft_subtract(ray.origin, sphere->position);
	values.a = ft_dot(ray.direction, ray.direction);
	values.b = 2.0f * ft_dot(test, ray.direction);
	values.c = ft_dot(test, test) - (sphere->radius * sphere->radius);
	tt = ft_cuadratic(values.a, values.b, values.c);
	if (tt.t0 > ray.hit.time && tt.t0 > 0)
	{
		ray.hit.time = tt.t0;
		ray.hit.point = ft_add(ray.origin, ft_multiply(ray.direction, ft_float_to_vec3(tt.t0)));
		ray.hit.normal = ft_normalice(ft_subtract(ray.hit.point, sphere->position));
		ray.hit.color = sphere->color;
		hit = true;
	}
}

int	ft_hit_anything(t_image *image, t_ray ray)
{
	bool	hit;

	hit = false;
	while (image->objects->sphere)
	{
		ft_hit_sphere(image, ray, &hit);
		image->objects->sphere = image->objects->sphere->next;
	}
}

static int	check_rgb(int color)
{
	if (color > 255)
		return (255);
	if (color < 0)
		return (0);
	return (color);
}

t_vec3	ft_color_scale(t_vec3 color, float f)
{
	t_vec3	rgb;

	rgb.r = check_rgb(f * (color.r >> 16));
	rgb.g = check_rgb(f * ((color.g >> 0x08) & 0xFF));
	rgb.b = check_rgb(f * (color.b & 0xFF));
	return (rgb);
}

t_vec3	ft_modifier_color()
{
	
}

t_vec3	ft_per_pixel(t_image *image, t_vec2 coord)
{
	t_image	*current;
	t_vec3	ambient_color;
	t_vec3	color;
	t_ray	ray;

	ray = ft_init_ray(image, coord);
	current = image;
	if (ft_hit_anything(current, ray) == 0);
		return ((t_vec3){{0.0f, 0.0f, 0.0f}});
	ambient_color = ft_color_scale(image->objects->ambient->color, image->objects->ambient->ambient_light);
	// color = 
	return ((t_vec3){{1.0f, 0.0f, 0.5f}});
}
