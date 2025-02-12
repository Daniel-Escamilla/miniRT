/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:57:18 by descamil          #+#    #+#             */
/*   Updated: 2025/02/10 18:11:23 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_free_all(t_image *image)
{
	if (image->objects)
	{
		if (image->objects->ambient)
			free(image->objects->ambient);
		if (image->objects->camera)
			free(image->objects->camera);
		if (image->objects->light)
			free(image->objects->light);
		if (image->objects->sphere)
			free(image->objects->sphere);
		if (image->objects->plane)
			free(image->objects->plane);
		if (image->objects->cylinder)
			free(image->objects->cylinder);
		free(image->objects);
	}
	if (image->data)
	{
		if (image->data->img)
			mlx_destroy_image(image->mlx, image->data->img);
		free(image->data);
	}
	if (image->mlx_win)
		mlx_destroy_window(image->mlx, image->mlx_win);
	if (image->mlx)
		free(image->mlx);
}

void print_vec3(t_vec3 vec)
{
    printf("{x: %.2f, y: %.2f, z: %.2f}", vec.x, vec.y, vec.z);
}

void print_objects(t_objects *objects)
{
	if (!objects)
	{
		printf(RD_1 "No objects to print.\n" RESET);
		return;
	}
	if (objects->ambient)
	{
		printf(B_YE_1 "=== Ambient ===\n" RESET);
		printf("Ambient Light: %.2f\n", objects->ambient->ambient_light);
		printf("Ambient Color: ");
		print_vec3(objects->ambient->color);
		printf("\n");
	}
	if (objects->camera)
	{
		printf(B_BL_0 "=== Camera ===\n" RESET);
		printf("Camera Position: ");
		print_vec3(objects->camera->position);
		printf("\n");
		printf("Camera Orientation: ");
		print_vec3(objects->camera->orientation);
		printf("\n");
		printf("Camera FOV: %d\n", objects->camera->fov);
	}
	if (objects->light)
	{
		printf(B_CY_0 "=== Light ===\n" RESET);
		printf("Light Brightness: %.2f\n", objects->light->brightness);
		printf("Light Position: ");
		print_vec3(objects->light->position);
		printf("\n");
		printf("Light Color: ");
		print_vec3(objects->light->color);
		printf("\n");
	}
	if (objects->sphere)
	{
		t_sphere *sphere = objects->sphere;
		while (sphere)
		{
			printf(B_RD_0 "=== Spheres ===\n" RESET);
			printf("Sphere Position: ");
			print_vec3(sphere->position);
			printf("\n");
			printf("Sphere Diameter: %.2f\n", sphere->diameter);
			printf("Sphere Color: ");
			print_vec3(sphere->color);
			printf("\n");
			sphere = sphere->next;
		}
	}
	if (objects->plane)
	{
		t_plane *plane = objects->plane;
		while (plane)
		{
			printf(B_GR_1 "=== Planes ===\n" RESET);
			printf("Plane Position: ");
			print_vec3(plane->position);
			printf("\n");
			printf("Plane Orientation: ");
			print_vec3(plane->orientation);
			printf("\n");
			printf("Plane Color: ");
			print_vec3(plane->color);
			printf("\n");
			plane = plane->next;
		}
	}
	if (objects->cylinder)
	{
		t_cylinder *cylinder = objects->cylinder;
		while (cylinder)
		{
			printf(B_OR_1 "=== Cylinders ===\n" RESET);
			printf("Cylinder Position: ");
			print_vec3(cylinder->position);
			printf("\n");
			printf("Cylinder Orientation: ");
			print_vec3(cylinder->orientation);
			printf("\n");
			printf("Cylinder Diameter: %.2f\n", cylinder->diameter);
			printf("Cylinder Height: %.2f\n", cylinder->height);
			printf("Cylinder Color: ");
			print_vec3(cylinder->color);
			printf("\n");
			cylinder = cylinder->next;
		}
	}
}

int main(int argc, char **argv)
{
	t_image image;

	(void) argc;
	(void) argv;
	ft_initialize(&image);

	if (ft_file_exist(argv, argc) == -1)
		return (-1);
	ft_create_struct(&image, argv);
	ft_create_window(image.data, &image);
	print_objects(image.objects);
	// mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);
	// mlx_loop(image.mlx);
	ft_free_all(&image);
	return (0);
}
