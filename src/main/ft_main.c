/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:57:18 by descamil          #+#    #+#             */
/*   Updated: 2025/04/13 17:38:33 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	ft_hooks(int key, t_image *image)
{
	if (key == 65307)
	{
		printf("%d\n", key);
		ft_end_program(image);
	}
	return (0);
}

void	ft_initialize(t_image *image)
{
	image->data = ft_calloc(sizeof(t_mlx), 1);
	image->width = 800;
	image->height = 800;
	image->objects = ft_calloc(sizeof(t_objects), 1);
}

void	ft_normalice_planes(t_plane *plane)
{
	t_plane	*current;

	current = plane;
	while(current)
	{
		current->normal = ft_normalice(current->normal);
		current = current->next;
	}
}

void	ft_normalice_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*current;

	current = cylinder;
	while(current)
	{
		current->normal = ft_normalice(current->normal);
		current = current->next;
	}
}

double ft_len_sqr(t_vec3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double ft_len(t_vec3 v)
{
    return sqrt(ft_len_sqr(v));
}

t_vec3 ft_normalice_camera(t_vec3 v)
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

int main(int argc, char **argv)
{
	t_image image;

	if (ft_file_exist(argv, argc) == -1)
		return (-1);
	ft_initialize(&image);
	ft_create_struct(&image, argv);
	ft_create_window(image.data, &image);
	ft_normalice_values(&image);
	// print_objects(image.objects);
	ft_create_render(image.data, &image);
	mlx_key_hook(image.mlx_win, ft_hooks, &image);
	mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);
	mlx_loop(image.mlx);
	ft_free_all(&image);
	return (0);
}
