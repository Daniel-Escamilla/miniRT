/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:21:28 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 21:21:59 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

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
		printf(B_YE_1 "\n=== Ambient ===\n\n" RESET);
		printf("Ambient Light: %.2f\n", objects->ambient->ambient_light);
		printf("Ambient Color: ");
		print_vec3(objects->ambient->color);
		printf("\n");
	}
	if (objects->camera)
	{
		printf(B_BL_0 "\n=== Camera ===\n\n" RESET);
		printf("Camera Position: ");
		print_vec3(objects->camera->position);
		printf("\n");
		printf("Camera Orientation: ");
		print_vec3(objects->camera->normal);
		printf("\n");
		printf("Camera FOV: %d\n", objects->camera->fov);
	}
	if (objects->light)
	{
		printf(B_CY_0 "\n=== Light ===\n\n" RESET);
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
			printf(B_RD_0 "\n=== Spheres ===\n\n" RESET);
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
			printf(B_GR_1 "\n=== Planes ===\n\n" RESET);
			printf("Plane Position: ");
			print_vec3(plane->position);
			printf("\n");
			printf("Plane Orientation: ");
			print_vec3(plane->normal);
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
			printf(B_OR_1 "\n=== Cylinders ===\n\n" RESET);
			printf("Cylinder Position: ");
			print_vec3(cylinder->position);
			printf("\n");
			printf("Cylinder Orientation: ");
			print_vec3(cylinder->normal);
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
