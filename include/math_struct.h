/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:04:44 by descamil          #+#    #+#             */
/*   Updated: 2025/04/07 21:21:51 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_STRUCT_H
# define MATH_STRUCT_H

# include "../minirt.h"

typedef union	u_vec2
{
	struct
	{
		float	x;
		float	y;
	};
	struct
	{
		float	t0;
		float	t1;
	};
}				t_vec2;

typedef union	u_vec3
{
	struct
	{
		int		r;
		int		g;
		int		b;
	};
	struct
	{
		float		x;
		float		y;
		float		z;
	};
	struct
	{
		float		a;
		float		b;
		float		c;
	};
	
}					t_vec3;

typedef struct	s_cam3
{
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
}				t_cam3;

typedef struct	s_hit
{
	t_vec3		normal;
	t_vec3		point;
	t_vec3		color;
	float		time;
}				t_hit;

typedef struct	s_ray
{
	t_vec3		origin;
	t_vec3		direction;
	t_hit		hit;
}				t_ray;


#endif
