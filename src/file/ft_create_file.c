/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:01:10 by descamil          #+#    #+#             */
/*   Updated: 2025/01/20 15:59:34 by descamil         ###   ########.fr       */
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

int	ft_check_rgb(t_vec3 color, int line)
{
	if (color.r < 0 || color.r > 255)
		printf("Line %d: R value (%f) out of range [0, 255]\n", line, color.r);
	else if (color.g < 0 || color.g > 255)
		printf("Line %d: G value (%f) out of range [0, 255]\n", line, color.g);
	else if (color.b < 0 || color.b > 255)
		printf("Line %d: B value (%f) out of range [0, 255]\n", line, color.b);
	else
		return (0);
	return (1);
}

int	ft_check_coords(t_vec3 xyz, int line)
{
	if (xyz.x == FLT_MIN || xyz.x == FLT_MAX)
		printf("Line %d: X value (%f) out of range\n", line, xyz.x);
	else if (xyz.y == FLT_MIN || xyz.y == FLT_MAX)
		printf("Line %d: Y value (%f) out of range\n", line, xyz.y);
	else if (xyz.z == FLT_MIN || xyz.z == FLT_MAX)
		printf("Line %d: Z value (%f) out of range\n", line, xyz.z);
	else
		return (0);
	return (1);
}

t_vec3	ft_split_colors(char *color, int *error, int line)
{
	t_vec3	rgb;
	char	**colors;

	colors = ft_split(color, ',');
	if (ft_strstr_len(colors) != 3)
		return ((t_vec3){{-1, -1, -1}});
	if (colors[0])
		rgb.r = ft_atoi(colors[0]);
	if (colors[1])
		rgb.g = ft_atoi(colors[1]);
	if (colors[2])
		rgb.b = ft_atoi(colors[2]);
	*error = ft_check_rgb(rgb, line);
	ft_strstr_free(colors);
	return (rgb);
}

void	ft_error_checking(char ***split, char *error, int status)
{
	ft_strstr_free(*split);
	printf("%s\n", error);
	exit(status);
}

float	ft_check_float(char *split, int *error, float min, float max, int line)
{
	float	atof;

	atof = ft_atof(split);
	printf("%f\n", atof);
	if (atof < min || atof > max)
	{
		printf("Line: %d, %f not in range [%f - %f]\n", line, atof, min, max);
		error += 1;
	}
	return (atof);
}

t_vec3	ft_split_coords(char *coord, int *error, int line)
{
	t_vec3	xyz;
	char	**coords;

	coords = ft_split(coord, ',');
	if (ft_strstr_len(coords) != 3)
		return ((t_vec3){{FLT_MAX, FLT_MAX, FLT_MAX}});
	if (coords[0])
		xyz.x = ft_atoi(coords[0]);
	if (coords[1])
		xyz.y = ft_atoi(coords[1]);
	if (coords[2])
		xyz.z = ft_atoi(coords[2]);
	*error = ft_check_coords(xyz, line);
	ft_strstr_free(coords);
	return (xyz);
}

t_vec3	ft_orientation(char *orientation, int *error, int line)
{
	char	**split;

	split = ft_split(orientation, ',');
	if (ft_strstr_len(split) != 3)
		return ((t_vec3){{-1, -1, -1}});
	if (split[0])
		ft_check_float(split[0], error, 0.0f, 1.0f, line);
	if (split[1])
		ft_check_float(split[1], error, 0.0f, 1.0f, line);
	if (split[2])
		ft_check_float(split[2], error, 0.0f, 1.0f, line);
	
	// ft_check_orientation()
	return ((t_vec3){{-1, -1, -1}});
}

void	ft_extact_ambient(t_image *image, char ***split, int *error, int line)
{
	if (ft_strstr_len(*split) != 3)
		ft_error_checking(split, "Ambient light missing\n"
			"Struct{A [0.0 - 1.0] [0,0,0 - 255,255,255]}", 1);
	image->objects->ambient = ft_calloc(sizeof(t_ambient), 1);
	image->objects->ambient->ambient_light = ft_check_float((*split)[1], error, 0.0f, 1.0f, line);
	image->objects->ambient->color = ft_split_colors((*split)[2], error, line);
}

void	ft_extact_camera(t_image *image, char ***split, int *error, int line)
{
	printf("%.10f\n", FLT_MAX);
	if (ft_strstr_len(*split) != 4)
		ft_error_checking(split, "Camera missing\nStruct{C [X,Y,Z]"
			" [0,0,1 || 0,1,0 || 1,0,0] [0 - 180]}", 1);
	image->objects->camera = ft_calloc(sizeof(t_camera), 1);
	image->objects->camera->position = ft_split_coords((*split)[1], error, line);
	image->objects->camera->orientation = ft_orientation((*split)[2], error, line);
	image->objects->camera->fov = (int)ft_check_float((*split)[3], error, 0, 180, line);
}

void	ft_extact_light(t_image *image, char ***split, int *error, int line)
{
	(void) image;
	(void) split;
	(void) error;
	(void) line;
}

void	ft_extact_sphere(t_image *image, char ***split, int *error, int line)
{
	(void) image;
	(void) split;
	(void) error;
	(void) line;
}

void	ft_extact_plane(t_image *image, char ***split, int *error, int line)
{
	(void) image;
	(void) split;
	(void) error;
	(void) line;
}

void	ft_extact_cylinder(t_image *image, char ***split, int *error, int line)
{
	(void) image;
	(void) split;
	(void) error;
	(void) line;
}

void	ft_process_line(t_image *image, char *content, int *error, int line)
{
	char	**split;

	if (ft_nothing(content, 0) == 1)
		return ;
	split = ft_split(content, ' ');
	if (split == NULL)
		return ;
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
	int		error;
	int		line;
	int		fd;

	error = 0;
	line = 1;
	fd = ft_open_file(argv);
	if (fd == -1)
		return ;
	content = get_next_line(fd);
	while (content != NULL)
	{
		content_clean = ft_strtrim(content, "\n");
		// printf(B_BL_0"LINE --> [%s]\n"RESET, content_clean);
		ft_process_line(image, content_clean, &error, line);
		free(content);
		free(content_clean);
		content = get_next_line(fd);
		line++;
	}
	
	// ft_fill_in(image);
}
