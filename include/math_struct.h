/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:04:44 by descamil          #+#    #+#             */
/*   Updated: 2025/06/14 10:23:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_STRUCT_H
# define MATH_STRUCT_H

# include "../minirt.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef FLT_MAX
#  define FLT_MAX 3.402823466e+38F
# endif

# ifndef FLT_MIN
#  define FLT_MIN 1.17549435e-38F
# endif

typedef union u_vec2
{
	struct
	{
		float		x;
		float		y;
	};
	struct
	{
		float		t0;
		float		t1;
	};
	struct
	{
		double		min;
		double		max;
	};
}				t_vec2;

typedef union u_vec3
{
	struct
	{
		double		x;
		double		y;
		double		z;
	};
	struct
	{
		int			r;
		int			g;
		int			b;
	};
	struct
	{
		float		_a;
		float		_b;
		float		_c;
	};
}					t_vec3;

typedef struct s_cam3
{
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
}				t_cam3;

typedef struct s_hit
{
	t_vec3		normal;
	t_vec3		point;
	t_vec3		color;
	float		time;
}				t_hit;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
	t_hit		*hit;
}				t_ray;

typedef struct s_cy_data
{
	bool		lateral_hit[2];
	bool		cap_hit;
	int			cap_side;
	float		axis_distance;
	t_vec3		ray_dir_proj;
	t_vec3		ray_origin_proj;
	t_vec3		vector_cylinder_to_ray;
	float		axis_test[2];
	float		radius;
	float		time;
	float		cap_time[2];
	t_vec3		cap_center[2];
	t_vec3		hit_point;
	t_vec2		cuadratic_tt;
	bool		cap_valid[2];
}				t_cy_data;

#endif
