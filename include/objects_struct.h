/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:51:11 by descamil          #+#    #+#             */
/*   Updated: 2025/01/14 10:23:37 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_STRUCT_H
# define OBJECTS_STRUCT_H

# include "../minirt.h"
# include "math_struct.h"

typedef struct s_ambient
{
	float		ambient_light;
	t_vec3		color;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		orientation;
	t_vec3		position;
	int			fov;
}				t_camera;

typedef struct s_light
{
	float		brightness;
	t_vec3		position;
	t_vec3		color;
}				t_light;

typedef	struct s_shpere
{
	t_vec3			position;
	float			diameter;
	t_vec3			color;
	struct s_shpere	*next;
}				t_shpere;

typedef struct s_plane
{
	t_vec3			orientation;
	t_vec3			position;
	t_vec3			color;
	struct s_plane	*next;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3				orientation;
	t_vec3				position;
	float				diameter;
	float				height;
	t_vec3				color;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct s_objects
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_shpere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_objects;

#endif
