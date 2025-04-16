/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:04:47 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:05:09 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	init_cylinder_cal(t_cylinder *cylinder, t_ray *ray, t_cy_data *d)
{
	t_vec3	tmp;
	t_vec3	tmp2;

	tmp = ft_scale(cylinder->normal, ft_dot(ray->direction, cylinder->normal));
	d->ray_dir_proj = ft_sub(ray->direction, tmp);
	tmp = ft_sub(ray->origin, cylinder->position);
	tmp2 = ft_scale(cylinder->normal, ft_dot(tmp, cylinder->normal));
	d->ray_origin_proj = ft_sub(tmp, tmp2);
	tmp._a = ft_length_squared(d->ray_dir_proj);
	tmp._b = 2.0f * ft_dot(d->ray_dir_proj, d->ray_origin_proj);
	tmp._c = ft_length_squared(d->ray_origin_proj) - d->radius * d->radius;
	d->cuadratic_tt = ft_cuadratic(tmp._a, tmp._b, tmp._c);
	d->vector_cylinder_to_ray = ft_sub(cylinder->position, ray->origin);
	d->axis_test[0] = ft_dot(cylinder->normal, ft_sub(ft_scale(ray->direction,
					d->cuadratic_tt.t0), d->vector_cylinder_to_ray));
	tmp = ft_scale(ray->direction, d->cuadratic_tt.t1);
	d->axis_test[1] = ft_dot(cylinder->normal,
			ft_sub(tmp, d->vector_cylinder_to_ray));
	d->lateral_hit[0] = (d->axis_test[0] >= 0 && d->axis_test[0]
			<= cylinder->height && d->cuadratic_tt.t0 > 0.0001);
	d->lateral_hit[1] = (d->axis_test[1] >= 0 && d->axis_test[1]
			<= cylinder->height && d->cuadratic_tt.t1 > 0.0001);
	d->cap_center[0] = cylinder->position;
	d->cap_center[1] = ft_add(cylinder->position,
			ft_scale(cylinder->normal, cylinder->height));
}

float	ft_hit_caps(t_cylinder *cylinder, t_cy_data *d, float result, int i)
{
	if (d->lateral_hit[0] && d->cuadratic_tt.t0 < result)
	{
		d->axis_distance = d->axis_test[0];
		result = d->cuadratic_tt.t0;
		d->cap_hit = false;
	}
	if (d->lateral_hit[1] && d->cuadratic_tt.t1 < result)
	{
		d->axis_distance = d->axis_test[1];
		result = d->cuadratic_tt.t1;
		d->cap_hit = false;
	}
	while (++i < 2)
	{
		if (d->cap_valid[i] && d->cap_time[i] < result)
		{
			d->cap_hit = true;
			d->cap_side = i;
			d->axis_distance = cylinder->height;
			if (i == 0)
				d->axis_distance = 0.0;
			result = d->cap_time[i];
		}
	}
	return (result);
}

void	cy_calc(t_cylinder *cylinder, t_ray *ray, t_cy_data *d)
{
	float	denom;
	int		i;

	i = -1;
	init_cylinder_cal(cylinder, ray, d);
	while (++i < 2)
	{
		denom = ft_dot(ray->direction, cylinder->normal);
		if (fabs(denom) > 1e-6)
		{
			d->cap_time[i] = ft_dot(ft_sub(d->cap_center[i],
						ray->origin), cylinder->normal) / denom;
			if (d->cap_time[i] > 0.0001)
			{
				d->hit_point = ft_add(ray->origin,
						ft_scale(ray->direction, d->cap_time[i]));
				if (ft_length_squared(ft_sub(d->hit_point,
							d->cap_center[i])) <= d->radius * d->radius)
					d->cap_valid[i] = true;
			}
		}
	}
	d->time = ft_hit_caps(cylinder, d, 1e30, -1);
}

void	ft_init_data(t_cylinder *cylinder, t_cy_data *d)
{
	d->cap_valid[0] = false;
	d->cap_valid[1] = false;
	d->cap_hit = false;
	d->cap_side = -1;
	d->radius = cylinder->diameter / 2;
}

void	ft_hit_cylinder(t_cylinder *cylinder, t_ray *ray, bool *hit)
{
	t_cy_data	d;

	ft_init_data(cylinder, &d);
	cy_calc(cylinder, ray, &d);
	if ((d.lateral_hit[0] || d.lateral_hit[1] || d.cap_hit)
		&& ray->hit->time > d.time && d.time > 0.0001)
	{
		ray->hit->time = d.time;
		ray->hit->point = ft_add(ray->origin, ft_scale(ray->direction, d.time));
		if (d.cap_hit)
		{
			ray->hit->normal = cylinder->normal;
			if (d.cap_side == 0)
				ray->hit->normal = ft_scale(cylinder->normal, -1);
		}
		else if (!d.lateral_hit[0] && d.lateral_hit[1])
			ray->hit->normal = ft_scale(ray->hit->normal, -1);
		else
			ray->hit->normal = ft_norm(ft_sub(ray->hit->point,
						ft_add(cylinder->position,
							ft_scale(cylinder->normal, d.axis_distance))));
		ray->hit->color = cylinder->color;
	}
	if (d.lateral_hit[0] || d.lateral_hit[1] || d.cap_hit)
		*hit = true;
}
