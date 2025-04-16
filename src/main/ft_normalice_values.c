/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalice_values.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:57:17 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 11:57:49 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_normalice_planes(t_plane *plane)
{
	t_plane	*current;

	current = plane;
	while (current)
	{
		current->normal = ft_normalice(current->normal);
		current = current->next;
	}
}

void	ft_normalice_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*current;

	current = cylinder;
	while (current)
	{
		current->normal = ft_normalice(current->normal);
		current = current->next;
	}
}

t_vec3	ft_normalice_camera(t_vec3 v)
{
	return (ft_scale(v, 1 / ft_len(v)));
}

void	ft_normalice_values(t_image *image)
{
	t_objects	*obj;

	obj = image->objects;
	obj->camera->normal = ft_normalice_camera(obj->camera->normal);
	obj->camera->fov = ((M_PI / 180) * obj->camera->fov);
	ft_normalice_planes(obj->plane);
	ft_normalice_cylinders(obj->cylinder);
}
