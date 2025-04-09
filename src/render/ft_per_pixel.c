/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_per_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:29:21 by descamil          #+#    #+#             */
/*   Updated: 2025/04/08 16:26:53 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"


t_vec3	ft_scale(t_vec3 value, float scale)
{
	return ((t_vec3){{(scale * value.x), (scale * value.y), (scale * value.z)}});
}

t_ray *ft_init_ray(t_image *image, t_vec2 coord)
{
	t_camera	*camera = image->objects->camera;
	t_vec3		horizontal_scaled;
	t_vec3		vertical_scaled;
    t_ray		*ray;

	ray = ft_calloc(sizeof(t_ray), 1);
	horizontal_scaled = ft_multiply(camera->horizontal, ft_float_to_vec3(coord.x));
	vertical_scaled = ft_multiply(camera->vertical, ft_float_to_vec3(coord.y));
    ray->origin = camera->position;
    ray->direction = ft_add(horizontal_scaled, vertical_scaled);
    ray->direction = ft_add(ray->direction, camera->l_left_corner);
    ray->direction = ft_normalice(ft_subtract(ray->direction, ray->origin));

	// printf("Ray Origin: (%f, %f, %f)\n", ray->origin.x, ray->origin.y, ray->origin.z);
	// printf("Ray Direction: (%f, %f, %f)\n", ray->direction.x, ray->direction.y, ray->direction.z);
	// exit(1);
	ray->hit.time = INFINITY;
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

void	ft_hit_sphere(t_image *image, t_ray *ray, bool *hit)
{
	t_sphere	*sphere;
	t_vec3		values;
	t_vec3		test;
	t_vec2		tt;

	sphere = image->objects->sphere;
	test = ft_subtract(ray->origin, sphere->position);
	values._a = ft_dot(ray->direction, ray->direction);
	values._b = 2.0f * ft_dot(test, ray->direction);
	values._c = ft_dot(test, test) - (sphere->radius * sphere->radius);
	tt = ft_cuadratic(values._a, values._b, values._c);
	printf("Sphere Position: (%f, %f, %f)\n", sphere->position.x, sphere->position.y, sphere->position.z);
	printf("Ray Origin: (%f, %f, %f)\n", ray->origin.x, ray->origin.y, ray->origin.z);
	printf("Ray Direction: (%f, %f, %f)\n", ray->direction.x, ray->direction.y, ray->direction.z);
	printf("Test Vector: (%f, %f, %f)\n", test.x, test.y, test.z);
	printf("Values a: %f, b: %f, c: %f\n", values._a, values._b, values._c);
	exit(1);
	if (tt.t0 > ray->hit.time && tt.t0 > 0)
	{
		printf("Aqui\n");
		ray->hit.time = tt.t0;
		ray->hit.point = ft_add(ray->origin, ft_multiply(ray->direction, ft_float_to_vec3(tt.t0)));
		ray->hit.normal = ft_normalice(ft_subtract(ray->hit.point, sphere->position));
		ray->hit.color = sphere->color;
		*hit = true;
	}
}

int	ft_hit_anything(t_image *image, t_ray *ray)
{
    bool		hit;
    t_sphere	*current_sphere;

    hit = false;
    current_sphere = image->objects->sphere; // Usar un puntero temporal
    while (current_sphere)
    {
        ft_hit_sphere(image, ray, &hit);
        current_sphere = current_sphere->next; // Avanzar en la lista
    }
    return (hit);
}

static int	check_rgb(int color)
{
	if (color > 255)
		return (255);
	if (color < 0)
		return (0);
	return (color);
}

t_vec3	ft_scale_color(t_vec3 color, float f)
{
	t_vec3	rgb;

	rgb.r = check_rgb(f * color.r);
	rgb.g = check_rgb(f * color.g);
	rgb.b = check_rgb(f * color.b);
	return (rgb);
}

t_vec3	ft_adjust_color(t_vec3 color, t_vec3 adjuster)
{
	t_vec3	rgb;

	rgb.r = check_rgb((((float)color.r / 255.0f) * ((float)adjuster.r / 255.0f)) * 255.0f);
    rgb.g = check_rgb((((float)color.g / 255.0f) * ((float)adjuster.g / 255.0f)) * 255.0f);
    rgb.b = check_rgb((((float)color.b / 255.0f) * ((float)adjuster.b / 255.0f)) * 255.0f);
	return (rgb);
}

float	ft_length_squared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3	ft_difuse_light(t_light *light, t_hit hit)
{
	t_vec3	light_dir;
	t_vec3	diffuse;
	float	intensity;
	float	gain;
	float	r2;

	light_dir = ft_subtract(light->position, hit.point);
	r2 = ft_length_squared(light_dir);
	light_dir = ft_normalice(light_dir);
	gain = ft_dot(light_dir, hit.normal);
	if (gain <= 0)
		return ((t_vec3){{0.0f, 0.0f, 0.0f}});
	intensity = (light->brightness * gain) / (4.0f * M_PI * r2);
	diffuse = ft_scale_color(hit.color, intensity);
	return (ft_adjust_color(diffuse, light->color));
}

int	ft_shadow(t_image *image, t_hit	hit)
{
	t_ray	shadow;
	int		touch;

	shadow.origin = ft_add(hit.point, ft_multiply(hit.normal, ft_float_to_vec3(0.001f)));
	shadow.direction = ft_normalice(ft_subtract(image->objects->light->position, shadow.origin));
	touch = ft_hit_anything(image, &shadow);
	return (touch);
}

t_vec3	ft_per_pixel(t_image *image, t_vec2 coord)
{
	t_image	*current;
	t_vec3	ambient_color;
	t_vec3	color;
	t_ray	*ray;

	ray = ft_init_ray(image, coord);
	current = image;
	if (ft_hit_anything(current, ray) == false)
		return ((t_vec3){{0.0f, 0.0f, 0.0f}});
	current = image;
	ambient_color = ft_scale_color(current->objects->ambient->color, current->objects->ambient->ambient_light);
	color = ft_adjust_color(ray->hit.color, ambient_color);
	if (ft_shadow(current, ray->hit))
		color = ft_adjust_color(color, ft_difuse_light(current->objects->light, ray->hit));
	// if (color.r != 0 && color.g != 0 && color.b != 0)
	// 	printf("Color --> %d, %d, %d\n", color.r, color.g, color.b);
	return (color);
}
