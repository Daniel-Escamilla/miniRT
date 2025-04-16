/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:02:30 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:02:54 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

void	ft_extact_sphere(t_image *image, char ***split, int *error, int line)
{
	t_sphere	*new_sphere;
	t_vec2		limit;

	if (ft_strstr_len(*split) != 4)
	{
		printf(B_RD_0 "Line [%d]\tExpected format 'sp [x,y,z]"
			" diameter [R,G,B]'" RESET "\n", line);
		(*error)++;
		return ;
	}
	limit.min = 0.0;
	limit.max = FLT_MAX;
	new_sphere = ft_calloc(sizeof(t_sphere), 1);
	new_sphere->position = ft_split_coords((*split)[1], error, line);
	new_sphere->diameter = ft_check_float((*split)[2],
			error, limit, line);
	new_sphere->color = ft_split_colors((*split)[3], error, line);
	new_sphere->radius = new_sphere->diameter / 2;
	ft_lstadd_back_general((void **)&image->objects->sphere, new_sphere);
}

void	ft_extact_plane(t_image *image, char ***split, int *error, int line)
{
	t_plane	*new_plane;

	if (ft_strstr_len(*split) != 4)
	{
		printf(B_RD_0 "Line [%d]\tExpected format 'pl [x,y,z]"
			" [vector] [R,G,B]'" RESET "\n", line);
		(*error)++;
		return ;
	}
	new_plane = ft_calloc(sizeof(t_plane), 1);
	new_plane->position = ft_split_coords((*split)[1], error, line);
	new_plane->normal = ft_split_coords((*split)[2], error, line);
	new_plane->color = ft_split_colors((*split)[3], error, line);
	ft_lstadd_back_general((void **)&image->objects->plane, new_plane);
}

void	ft_extact_cylinder(t_image *image, char ***split, int *error, int line)
{
	t_cylinder	*new_cylinder;
	t_vec2		limit;

	if (ft_strstr_len(*split) != 6)
	{
		printf(B_RD_0 "Line [%d]\tExpected format 'cy [x,y,z] "
			"[vector] diameter height [R,G,B]'" RESET "\n", line);
		(*error)++;
		return ;
	}
	limit.min = 0.0f;
	limit.max = FLT_MAX;
	new_cylinder = ft_calloc(sizeof(t_cylinder), 1);
	new_cylinder->position = ft_split_coords((*split)[1], error, line);
	new_cylinder->normal = ft_split_coords((*split)[2], error, line);
	new_cylinder->diameter = ft_check_float((*split)[3],
			error, limit, line);
	new_cylinder->height = ft_check_float((*split)[4],
			error, limit, line);
	new_cylinder->color = ft_split_colors((*split)[5], error, line);
	new_cylinder->radius = new_cylinder->diameter / 2;
	ft_lstadd_back_general((void **)&image->objects->cylinder, new_cylinder);
}
