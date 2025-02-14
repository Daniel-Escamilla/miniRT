/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:04:44 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 21:17:22 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_STRUCT_H
# define MATH_STRUCT_H

# include "../minirt.h"

typedef struct
{
	float	x;
	float	y;
} 		t_vec2;

typedef union u_vec3
{
	struct
	{
		float		r;
		float		g;
		float		b;
	};
	struct
	{
		float		x;
		float		y;
		float		z;
	};
	struct
	{
		float		v1;
		float		v2;
		float		v3;
	};
}					t_vec3;

#endif
