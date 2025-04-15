/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_per_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:29:21 by descamil          #+#    #+#             */
/*   Updated: 2025/04/15 16:03:17 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

int	ft_hit_anything(t_image *image, t_ray *ray);

double	ft_length_squared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3		ft_norm(t_vec3 v)
{
	return (ft_scale(v, 1 / sqrt(ft_length_squared(v))));
}

t_vec3	ft_scale(t_vec3 value, double scale)
{
	t_vec3	result;
	
	result.x = scale * value.x;
	result.y = scale * value.y;
	result.z = scale * value.z;
	return (result);
}

t_ray *ft_init_ray(t_image *image, t_vec2 coord)
{
	t_camera	*camera = image->objects->camera;
	t_vec3		horizontal_scaled;
	t_vec3		vertical_scaled;
    t_ray		*ray;

	ray = ft_calloc(sizeof(t_ray), 1);
	ray->hit = ft_calloc(sizeof(t_hit), 1);
	horizontal_scaled = ft_multiply(camera->horizontal, ft_float_to_vec3(coord.x));
	vertical_scaled = ft_multiply(camera->vertical, ft_float_to_vec3(coord.y));
    ray->origin = camera->position;
    ray->direction = ft_add(horizontal_scaled, vertical_scaled);
    ray->direction = ft_add(ray->direction, camera->l_left_corner);
    ray->direction = ft_normalice(ft_subtract(ray->direction, ray->origin));
    return (ray);
}

t_vec2	ft_cuadratic(double a, double b, double c)
{
	t_vec2	values;
	double	disc;
	double	tmp;

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

void	ft_hit_sphere(t_sphere *sphere, t_ray *ray, bool *hit)
{
	t_vec3		values;
	t_vec3		test;
	t_vec2		tt;

	test = ft_subtract(ray->origin, sphere->position);
	values._a = ft_dot(ray->direction, ray->direction);
	values._b = 2.0f * ft_dot(test, ray->direction);
	values._c = ft_dot(test, test) - (sphere->radius * sphere->radius);
	tt = ft_cuadratic(values._a, values._b, values._c);
	if (tt.t0 < ray->hit->time && tt.t0 > 0)
	{
		ray->hit->time = tt.t0;
		ray->hit->point = ft_add(ray->origin, ft_multiply(ray->direction, ft_float_to_vec3(tt.t0)));
		ray->hit->normal = ft_normalice(ft_subtract(ray->hit->point, sphere->position));
		ray->hit->color = sphere->color;
		*hit = true;
	}
}

void	ft_hit_plane(t_plane *plane, t_ray *ray, bool *hit)
{
	double	test;
	double	tt;

	test = ft_dot(ft_norm(ray->direction), plane->normal);
	if (test >= 0.0)
		return;
	tt = ft_dot(ft_subtract(plane->position, ray->origin), plane->normal) / test;
	if (tt < ray->hit->time && tt > 0.0001)
	{
		ray->hit->time = tt;
		ray->hit->point = ft_add(ray->origin, ft_scale(ray->direction, ray->hit->time));
		ray->hit->normal = plane->normal;
		ray->hit->color = plane->color;
		*hit = true;
	}
}

static float	cy_calc(t_cylinder *cylinder, t_ray *ray, float *y, bool ret[2], bool *cap_hit, int *cap_side)
{
	t_vec3	v[2];
	t_vec3	v_cy2ray;
	t_vec2	tt;
	float	dist[2];
	float	radius;
	float	t_cap[2];
	t_vec3	cap_center[2];
	t_vec3	hit_point;
	float	t_result;
	bool	valid_cap[2] = {false, false};

	*cap_hit = false;
	*cap_side = -1;
	radius = cylinder->diameter / 2.0;

	// Cuerpo
	v[0] = ft_subtract(ray->direction, ft_scale(cylinder->normal, ft_dot(ray->direction, cylinder->normal)));
	v[1] = ft_subtract(ft_subtract(ray->origin, cylinder->position),
		ft_scale(cylinder->normal, ft_dot(ft_subtract(ray->origin, cylinder->position), cylinder->normal)));
	tt = ft_cuadratic(ft_length_squared(v[0]), 2 * ft_dot(v[0], v[1]), ft_length_squared(v[1]) - radius * radius);

	v_cy2ray = ft_subtract(cylinder->position, ray->origin);
	dist[0] = ft_dot(cylinder->normal, ft_subtract(ft_scale(ray->direction, tt.t0), v_cy2ray));
	dist[1] = ft_dot(cylinder->normal, ft_subtract(ft_scale(ray->direction, tt.t1), v_cy2ray));
	ret[0] = (dist[0] >= 0 && dist[0] <= cylinder->height && tt.t0 > 0.0001);
	ret[1] = (dist[1] >= 0 && dist[1] <= cylinder->height && tt.t1 > 0.0001);

	// Tapas
	cap_center[0] = cylinder->position;
	cap_center[1] = ft_add(cylinder->position, ft_scale(cylinder->normal, cylinder->height));

	for (int i = 0; i < 2; i++)
	{
		float denom = ft_dot(ray->direction, cylinder->normal);
		if (fabs(denom) > 1e-6)
		{
			t_cap[i] = ft_dot(ft_subtract(cap_center[i], ray->origin), cylinder->normal) / denom;
			if (t_cap[i] > 0.0001)
			{
				hit_point = ft_add(ray->origin, ft_scale(ray->direction, t_cap[i]));
				if (ft_length_squared(ft_subtract(hit_point, cap_center[i])) <= radius * radius)
					valid_cap[i] = true;
			}
		}
	}

	// Elegir el tiempo más cercano válido
	t_result = 1e30;
	if (ret[0] && tt.t0 < t_result)
	{
		*y = dist[0];
		t_result = tt.t0;
		*cap_hit = false;
	}
	if (ret[1] && tt.t1 < t_result)
	{
		*y = dist[1];
		t_result = tt.t1;
		*cap_hit = false;
	}
	for (int i = 0; i < 2; i++)
	{
		if (valid_cap[i] && t_cap[i] < t_result)
		{
			*cap_hit = true;
			*cap_side = i;
			*y = i == 0 ? 0.0 : cylinder->height;
			t_result = t_cap[i];
		}
	}
	return (t_result);
}

void	ft_hit_cylinder(t_cylinder *cylinder, t_ray *ray, bool *hit)
{
	bool		ret[2];
	bool		cap_hit;
	int			cap_side;
	float		time;
	float		y;

	time = cy_calc(cylinder, ray, &y, ret, &cap_hit, &cap_side);
	if ((ret[0] || ret[1] || cap_hit) && ray->hit->time > time && time > 0.0001)
	{
		ray->hit->time = time;
		ray->hit->point = ft_add(ray->origin, ft_scale(ray->direction, time));
		if (cap_hit)
			ray->hit->normal = (cap_side == 0) ? ft_scale(cylinder->normal, -1) : cylinder->normal;
		else if (!ret[0] && ret[1])
			ray->hit->normal = ft_scale(ray->hit->normal, -1);
		else
			ray->hit->normal = ft_norm(ft_subtract(ray->hit->point,
				ft_add(cylinder->position, ft_scale(cylinder->normal, y))));
		ray->hit->color = cylinder->color;
	}
	if (ret[0] || ret[1] || cap_hit)
		*hit = true;
}

int	ft_hit_anything(t_image *image, t_ray *ray)
{
	bool		hit;
    t_sphere	*current_sphere;
	t_plane		*current_plane;
	t_cylinder	*current_cylinder;

    ray->hit->time = INFINITY;
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

static int	check_rgb(int color)
{
	if (color > 255)
		return (255);
	if (color < 0)
		return (0);
	return (color);
}

t_vec3	ft_scale_color(t_vec3 color, double f)
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

	rgb.r = check_rgb(((color.r / 255.0f) * (adjuster.r / 255.0f)) * 255.0f);
    rgb.g = check_rgb(((color.g / 255.0f) * (adjuster.g / 255.0f)) * 255.0f);
    rgb.b = check_rgb(((color.b / 255.0f) * (adjuster.b / 255.0f)) * 255.0f);
	return (rgb);
}

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_vec3	ft_difuse_light(t_light *light, t_hit *hit)
{
	t_vec3	light_dir;
	t_vec3	diffuse;
	double	intensity;
	double	gain;
	double	r2;

	light_dir = ft_subtract(light->position, hit->point);
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
	shadow->direction = ft_norm(ft_subtract(image->objects->light->position, shadow->origin));
	touch = ft_hit_anything(image, shadow);
	free(shadow->hit);
	free(shadow);
	return (touch);
}

void	ft_print_color(t_vec3 color)
{
	printf("X -> %d\t", color.r);
	printf("Y -> %d\t", color.g);
	printf("Z -> %d\n", color.b);
}

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

t_vec3	ft_light_point(t_light *light, t_hit *hit, t_vec3 color)
{
	t_vec3	diffuse_light;
	t_vec3	result;

	diffuse_light = ft_difuse_light(light, hit);
	result = ft_add(diffuse_light, color);
	return (ft_clamp(result));
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
	if (ft_hit_anything(current, ray) == 0)
	{
		free(ray->hit);
		free(ray);
		return ((t_vec3){{0.0f, 0.0f, 0.0f}});
	}
	current = image;
	ambient_color = ft_scale_color(current->objects->ambient->color, current->objects->ambient->ambient_light);
	color = ft_adjust_color(ray->hit->color, ambient_color);
	if (!ft_shadow(current, ray->hit))
		color = ft_light_point(current->objects->light, ray->hit, color);
	free(ray->hit);
	free(ray);
	return (color);
}
