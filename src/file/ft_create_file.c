/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:01:10 by descamil          #+#    #+#             */
/*   Updated: 2025/02/09 12:38:33 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

t_vec3	ft_float_to_vec3(float a)
{
	t_vec3	result;

	result.x = a;
	result.y = a;
	result.z = a;
	return (result);
}

int	ft_nothing(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\n'))
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

// int	ft_check_rgb(t_vec3 color, int line)
// {
// 	if (color.r < 0 || color.r > 255)
// 		printf("Line %d: R value (%f) out of range [0, 255]\n", line, color.r);
// 	else if (color.g < 0 || color.g > 255)
// 		printf("Line %d: G value (%f) out of range [0, 255]\n", line, color.g);
// 	else if (color.b < 0 || color.b > 255)
// 		printf("Line %d: B value (%f) out of range [0, 255]\n", line, color.b);
// 	else
// 		return (0);
// 	return (1);
// }

// int	ft_check_coords(t_vec3 xyz, int line)
// {
// 	if (xyz.x == -FLT_MAX || xyz.x == FLT_MAX)
// 		printf("Line %d: X value (%f) out of range\n", line, xyz.x);
// 	else if (xyz.y == -FLT_MAX || xyz.y == FLT_MAX)
// 		printf("Line %d: Y value (%f) out of range\n", line, xyz.y);
// 	else if (xyz.z == -FLT_MAX || xyz.z == FLT_MAX)
// 		printf("Line %d: Z value (%f) out of range\n", line, xyz.z);
// 	else
// 		return (0);
// 	return (1);
// }

float	ft_check_float(char *split, int *error, float min, float max, int line)
{
	float	atof;

	atof = ft_atof(split);
	if (atof < min || atof > max)
	{
		printf("Line: %d, %f not in range [%f - %f]\n", line, atof, min, max);
		*error += 1;
	}
	return (atof);
}

float ft_value_normal(char *value, int *error, int line)
{
    float	num;

	 num = ft_atof(value);
    if (num != 0.000000f && num != 1.000000f)
    {
        printf("Line: %d, %f not in range [0 - 1]\n", line, num);
        *error += 1;
        return (-1);
    }
    return (num);
}

t_vec3	ft_split_colors(char *color, int *error, int line)
{
	t_vec3	rgb;
	char	**colors;

	colors = ft_split(color, ',');
	if (ft_strstr_len(colors) != 3)
		return ((t_vec3){{-1, -1, -1}});
	rgb.r = ft_check_float(colors[0], error, 0, 255, line);
	rgb.g = ft_check_float(colors[1], error, 0, 255, line);
	rgb.b = ft_check_float(colors[2], error, 0, 255, line);
	ft_strstr_free(colors);
	return (rgb);
}

void	ft_error_checking(char ***split, char *error, int status)
{
	ft_strstr_free(*split);
	printf("%s\n", error);
	exit(status);
}

t_vec3	ft_split_coords(char *coord, int *error, int line)
{
	t_vec3	xyz;
	char	**coords;

	coords = ft_split(coord, ',');
	if (ft_strstr_len(coords) != 3)
		return ((t_vec3){{FLT_MAX, FLT_MAX, FLT_MAX}});
	xyz.x = ft_check_float(coords[0], error, -FLT_MAX, FLT_MAX, line);
	xyz.y = ft_check_float(coords[1], error, -FLT_MAX, FLT_MAX, line);
	xyz.z = ft_check_float(coords[2], error, -FLT_MAX, FLT_MAX, line);
	ft_strstr_free(coords);
	return (xyz);
}

t_vec3	ft_orientation(char *orientation, int *error, int line)
{
	char	**split;
	t_vec3	orient;

	split = ft_split(orientation, ',');
	if (ft_strstr_len(split) != 3)
		return ((t_vec3){{-1, -1, -1}});
	orient.x = ft_check_float(split[0], error, 0.0f, 1.0f, line);
	orient.y = ft_check_float(split[1], error, 0.0f, 1.0f, line);
	orient.z = ft_check_float(split[2], error, 0.0f, 1.0f, line);
	ft_strstr_free(split);
	return (orient);
}

int	ft_only_one(t_vec3 values)
{
	if (values.x == 1.0f && values.y == 0.0f && values.z == 0.0f)
		return (1);
	if (values.x == 0.0f && values.y == 1.0f && values.z == 0.0f)
		return (1);
	if (values.x == 0.0f && values.y == 0.0f && values.z == 1.0f)
		return (1);
	return (0);
}

t_vec3	ft_check_normal(char *normal, int *error, int line)
{
	char	**split;
	t_vec3	values;

	split = ft_split(normal, ',');
	if (ft_strstr_len(split) != 3)
		return ((t_vec3){{-1, -1, -1}});
	values.x = ft_value_normal(split[0], error, line);
	values.y = ft_value_normal(split[1], error, line);
	values.z = ft_value_normal(split[2], error, line);
	if (ft_only_one(values))
		return (values);
	return ((t_vec3){{-1, -1, -1}});
}

void	ft_extact_ambient(t_image *image, char ***split, int *error, int line)
{
	if (ft_strstr_len(*split) != 3)
		ft_error_checking(split, "Ambient light missing\n"
			"A [ambient lighting ratio (0.0 - 1.0)] [R,G,B (0-255)]", 1);
	image->objects->ambient = ft_calloc(sizeof(t_ambient), 1);
	image->objects->ambient->ambient_light = ft_check_float((*split)[1], error, 0.0f, 1.0f, line);
	image->objects->ambient->color = ft_split_colors((*split)[2], error, line);
}

void	ft_extact_camera(t_image *image, char ***split, int *error, int line)
{
	if (ft_strstr_len(*split) != 4)
		ft_error_checking(split, "Camera missing\nC [x,y,z coordinates]"
			" [orientation vector (-1 to 1)] [FOV (0-180)]", 1);
	image->objects->camera = ft_calloc(sizeof(t_camera), 1);
	image->objects->camera->position = ft_split_coords((*split)[1], error, line);
	image->objects->camera->orientation = ft_orientation((*split)[2], error, line);
	image->objects->camera->fov = (int)ft_check_float((*split)[3], error, 0, 180, line);
}

void	ft_extact_light(t_image *image, char ***split, int *error, int line)
{
	if (ft_strstr_len(*split) != 4)
		ft_error_checking(split, "Light missing\nL [x,y,z coordinates]"
		" [brightness ratio (0.0 - 1.0)] [R,G,B (0-255)]", 1);
	image->objects->light = ft_calloc(sizeof(t_light), 1);
	image->objects->light->position = ft_split_coords((*split)[1], error, line);
	image->objects->light->brightness = ft_check_float((*split)[2], error, 0.0f, 1.0f, line);
	image->objects->light->color = ft_split_colors((*split)[3], error, line);
}

void	ft_extact_sphere(t_image *image, char ***split, int *error, int line)
{
	t_sphere	*new_sphere;

	if (ft_strstr_len(*split) != 4)
		ft_error_checking(split, "Sphere missing\n sp [x,y,z coordinates]"
			" [diameter] [R,G,B (0-255)]", 1);
	new_sphere = ft_calloc(sizeof(t_sphere), 1);
	new_sphere->position = ft_split_coords((*split)[1], error, line);
	new_sphere->diameter = ft_check_float((*split)[2], error, 0.0f, FLT_MAX, line);
	new_sphere->color = ft_split_colors((*split)[3], error, line);
	new_sphere->next = image->objects->sphere;
	image->objects->sphere = new_sphere;
}

void	ft_extact_plane(t_image *image, char ***split, int *error, int line)
{
	t_plane	*new_plane;
	
	if (ft_strstr_len(*split) != 4)
		ft_error_checking(split, "Plane missing\npl [x,y,z coordinates]"
			" [normal vector (-1 to 1)] [R,G,B (0-255)]", 1);
	new_plane = ft_calloc(sizeof(t_plane), 1);
	new_plane->position = ft_split_coords((*split)[1], error, line);
	new_plane->orientation = ft_check_normal((*split)[2], error, line);
	new_plane->color = ft_split_colors((*split)[3], error, line);
	new_plane->next = image->objects->plane;
	image->objects->plane = new_plane;
}

void	ft_extact_cylinder(t_image *image, char ***split, int *error, int line)
{
	t_cylinder	*new_cylinder;

	if (ft_strstr_len(*split) != 6)
		ft_error_checking(split, "Cylinder missing\ncy [x,y,z coordinates]"
			" [axis vector (-1 to 1)] [diameter] [height] [R,G,B (0-255)]", 1);
	new_cylinder = ft_calloc(sizeof(t_cylinder), 1);
	new_cylinder->position = ft_split_coords((*split)[1], error, line);
	new_cylinder->orientation = ft_check_normal((*split)[2], error, line);
	new_cylinder->diameter = ft_check_float((*split)[3], error, 0.0f, FLT_MAX, line);
	new_cylinder->color = ft_split_colors((*split)[4], error, line);
	new_cylinder->height = ft_check_float((*split)[5], error, 0.0f, FLT_MAX, line);
	new_cylinder->next = image->objects->cylinder;
	image->objects->cylinder = new_cylinder;
}

void	ft_process_line(t_image *image, char *content, int *error, int line)
{
	char	**split;

	if (ft_nothing(content, 0) == 1)
		return ;
	split = ft_split(content, ' ');
	if (split == NULL)
		return ;
	printf("%s\n", split[0]);
	if (ft_strnstr("ACLspplcy", split[0], 10) == NULL)
	{
		ft_strstr_free(split);
		return ;
	}
	else if (ft_strnstr(split[0], "A", 1) != NULL)
		ft_extact_ambient(image, &split, error, line);
	else if (ft_strnstr(split[0], "C", 1) != NULL && ft_strlen(split[0]) == 1)
		ft_extact_camera(image, &split, error, line);
	else if (ft_strnstr(split[0], "L", 1) != NULL && ft_strlen(split[0]) == 1)
		ft_extact_light(image, &split, error, line);
	else if (ft_strnstr(split[0], "sp", 2) != NULL && ft_strlen(split[0]) == 2)
		ft_extact_sphere(image, &split, error, line);
	else if (ft_strnstr(split[0], "pl", 2) != NULL && ft_strlen(split[0]) == 2)
		ft_extact_plane(image, &split, error, line);
	else if (ft_strnstr(split[0], "cy", 2) != NULL && ft_strlen(split[0]) == 2)
		ft_extact_cylinder(image, &split, error, line);
	ft_strstr_free(split);
}

void	ft_create_struct(t_image *image, char **argv)
{
	char	*content;
	char	*content_clean;
	t_image	*current_image;
	int		error;
	int		line;
	int		fd;

	error = 0;
	line = 1;
	current_image = image;
	fd = ft_open_file(argv);
	if (fd == -1)
		return ;
	content = get_next_line(fd);
	while (content != NULL)
	{
		content_clean = ft_strtrim(content, "\n");
		// printf(B_BL_0"LINE --> [%s]\n"RESET, content_clean);
		ft_process_line(current_image, content_clean, &error, line);
		free(content);
		free(content_clean);
		content = get_next_line(fd);
		line++;
	}
	
	// ft_fill_in(image);
}
