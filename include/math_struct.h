/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:04:44 by descamil          #+#    #+#             */
/*   Updated: 2024/11/03 11:45:36 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_STRUCT_H
# define MATH_STRUCT_H

typedef struct s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef union u_vec3
{
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	struct
	{
		float	r;
		float	g;
		float	b;
	};
}				t_vec3;

typedef struct s_matrix_v3
{
	t_vec3		x;
	t_vec3		y;
	t_vec3		z;
}				t_matrix_v3;

typedef struct s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct s_matrix_v4
{
	t_vec4		x;
	t_vec4		y;
	t_vec4		z;
	t_vec4		w;
}				t_matrix_v4;

#endif
