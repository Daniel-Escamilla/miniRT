/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:57:18 by descamil          #+#    #+#             */
/*   Updated: 2025/04/14 14:51:56 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_move_camera(int key, t_image *image)
{
	static int	sign = 1;
	t_vec3		*normal = &image->objects->camera->normal;
	t_vec3		*position = &image->objects->camera->position;

	if (key == '+')
		sign = 1;
	else if (key == '-')
		sign = -1;
	else if (key == 'x')
		normal->x += sign * 0.1;
	else if (key == 'y')
		normal->y += sign * 0.1;
	else if (key == 'z')
		normal->z += sign * 0.1;
	else if (key == 'X')
		normal->x -= sign * 0.1;
	else if (key == 'Y')
		normal->y -= sign * 0.1;
	else if (key == 'Z')
		normal->z -= sign * 0.1;
	else if (key == 65363) // Left arrow
		position->x -= sign * 0.5;
	else if (key == 65361) // Right arrow
		position->x += sign * 0.5;
	else if (key == 65362) // Up arrow
		position->z += sign * 0.5;
	else if (key == 65364) // Down arrow
		position->z -= sign * 0.5;
	else if (key == 'f')
		image->objects->camera->fov += sign * 5;
	else if (key == 'F')
		image->objects->camera->fov -= sign * 5;
	if (key == 'f' || key == 'F' || key == 'x' || key == 'y' || key == 'z' || 
		key == 'X' || key == 'Y' || key == 'Z' || key == 65363 || key == 65361 || 
		key == 65362 || key == 65364)
	{
		printf("Camera FOV: %f\n", image->objects->camera->fov);
		printf("Camera Normal: x=%f, y=%f, z=%f\n", normal->x, normal->y, normal->z);
		printf("Camera Position: x=%f, y=%f, z=%f\n", position->x, position->y, position->z);
	}
	ft_create_render(image->data, image);
}

int	ft_hooks(int key, t_image *image)
{
	if (key == 65307)
	{
		printf("%d\n", key);
		ft_end_program(image);
	}
	ft_move_camera(key, image);
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
