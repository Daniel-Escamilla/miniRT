/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:57:18 by descamil          #+#    #+#             */
/*   Updated: 2025/06/14 13:08:34 by descamil         ###   ########.fr       */
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
		normal->x += sign * 0.01;
	else if (key == 'y')
		normal->y += sign * 0.01;
	else if (key == 'z')
		normal->z += sign * 0.01;
	else if (key == 'X')
		normal->x -= sign * 0.01;
	else if (key == 'Y')
		normal->y -= sign * 0.01;
	else if (key == 'Z')
		normal->z -= sign * 0.01;
	else if (key == 65363) // Left arrow
		position->x -= sign * 0.1;
	else if (key == 65361) // Right arrow
		position->x += sign * 0.1;
	else if (key == 65362) // Up arrow
		position->z += sign * 0.1;
	else if (key == 65364) // Down arrow
		position->z -= sign * 0.1;
	else if (key == 103) // Up arrow
		position->y += sign * 0.1;
	else if (key == 104) // Down arrow
		position->y -= sign * 0.1;
	else if (key == 'f')
		image->objects->camera->fov += sign * 5;
	else if (key == 'F')
		image->objects->camera->fov -= sign * 5;
	// if (key == 'f' || key == 'F' || key == 'x' || key == 'y' || key == 'z' || 
	// 	key == 'X' || key == 'Y' || key == 'Z' || key == 65363 || key == 65361 || 
	// 	key == 65362 || key == 65364)
	// {
	// 	printf("Camera FOV: %f\n", image->objects->camera->fov);
	// 	printf("Camera Normal: x=%f, y=%f, z=%f\n", normal->x, normal->y, normal->z);
	// 	printf("Camera Position: x=%f, y=%f, z=%f\n", position->x, position->y, position->z);
	// }
	ft_create_render(image->data, image);
}
int	ft_hooks(int key, t_image *image)
{
	if (key == 65307)
		ft_end_program(image);
	printf("%d\n", key);
	ft_move_camera(key, image);
	return (0);
}

void	ft_initialize(t_image *image)
{
	image->data = ft_calloc(sizeof(t_mlx), 1);
	image->width = 200;
	image->height = 200;
	image->objects = ft_calloc(sizeof(t_objects), 1);
}

int	main(int argc, char **argv)
{
	t_image	image;

	if (ft_file_exist(argv, argc) == -1)
		return (-1);
	ft_initialize(&image);
	ft_create_struct(&image, argv);
	ft_create_window(image.data, &image);
	ft_normalice_values(&image);
	ft_create_render(image.data, &image);
	mlx_key_hook(image.mlx_win, ft_hooks, &image);
	mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);
	mlx_loop(image.mlx);
	ft_free_all(&image);
	return (0);
}
