/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:58:40 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:02:11 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

void	ft_extact_ambient(t_image *image, char ***split, int *error, int line)
{
	t_vec2	limit;

	if (ft_strstr_len(*split) != 3)
	{
		printf(B_RD_0 "Line [%d]\tExpected format 'A"
			" ratio [R,G,B]'" RESET "\n", line);
		(*error)++;
		return ;
	}
	limit.min = 0.0f;
	limit.max = 1.0f;
	image->objects->ambient = ft_calloc(sizeof(t_ambient), 1);
	image->objects->ambient->ambient_light = ft_check_float((*split)[1],
			error, limit, line);
	image->objects->ambient->color = ft_split_colors((*split)[2], error, line);
}

void	ft_extact_camera(t_image *image, char ***split, int *error, int line)
{
	t_vec2	limit;

	if (ft_strstr_len(*split) != 4)
	{
		printf(B_RD_0 "Line [%d]\tExpected format 'C [x,y,z]"
			" [vector] FOV'" RESET "\n", line);
		(*error)++;
		return ;
	}
	limit.min = 0;
	limit.max = 180;
	image->objects->camera = ft_calloc(sizeof(t_camera), 1);
	image->objects->camera->position = ft_split_coords((*split)[1],
			error, line);
	image->objects->camera->normal = ft_split_coords((*split)[2], error, line);
	image->objects->camera->fov = (int)ft_check_float((*split)[3],
			error, limit, line);
}

void	ft_extact_light(t_image *image, char ***split, int *error, int line)
{
	t_vec2	limit;

	if (ft_strstr_len(*split) != 4)
	{
		printf(B_RD_0 "Line [%d]\tExpected format 'L [x,y,z]"
			" ratio [R,G,B]'" RESET "\n", line);
		(*error)++;
		return ;
	}
	limit.min = 0.0;
	limit.max = 1.0;
	image->objects->light = ft_calloc(sizeof(t_light), 1);
	image->objects->light->position = ft_split_coords((*split)[1],
			error, line);
	image->objects->light->brightness = ft_check_float((*split)[2], error,
			limit, line);
	image->objects->light->color = ft_split_colors((*split)[3], error, line);
}
