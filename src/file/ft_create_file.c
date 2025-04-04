/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:01:10 by descamil          #+#    #+#             */
/*   Updated: 2025/04/04 16:30:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

void	 ft_lstadd_back_general(void **list, void *new)
{
	void	*current;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (*(void **)current != NULL)
		current = *(void **)current;
	*(void **)current = new;
}

t_vec3	ft_float_to_vec3(float a)
{
	t_vec3	result;

	result.x = a;
	result.y = a;
	result.z = a;
	return (result);
}

int	ft_nothing(const char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\n'))
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

double	ft_check_float(char *split, int *error, float min, float max, int line)
{
	double	atof;

	atof = ft_atof(split);
	if (atof < min || atof > max || (signbit(atof) && atof == -0.0F))
	{
		if (min == -FLT_MAX && max == FLT_MAX)
			printf(B_RD_0"Line [%d]\t%f not in range [{-FLT_MAX} - {FLT_MAX}]\n"RESET, line, atof);
		else if (max == FLT_MAX)
			printf(B_RD_0"Line [%d]\t%f not in range [{%f} - {FLT_MAX}]\n"RESET, line, atof, min);
		else
			printf(B_RD_0"Line [%d]\t%f not in range [%f - %f]\n"RESET, line, atof, min, max);
		(*error)++;
	}
	return (atof);
}

t_vec3	ft_split_colors(char *color, int *error, int line)
{
	t_vec3	rgb;
	char	**colors;

	colors = ft_split(color, ',');
	if (ft_strstr_len(colors) != 3)
	{
		(*error)++;
		printf(B_RD_0"Line [%d]\tColors not set\n"RESET, line);
		return ((t_vec3){{-1, -1, -1}});
	}
	rgb.r = ft_check_float(colors[0], error, 0, 255, line);
	rgb.g = ft_check_float(colors[1], error, 0, 255, line);
	rgb.b = ft_check_float(colors[2], error, 0, 255, line);
	ft_strstr_free(colors);
	return (rgb);
}

t_vec3	ft_split_coords(char *coord, int *error, int line)
{
	t_vec3	xyz;
	char	**coords;

	coords = ft_split(coord, ',');
	if (ft_strstr_len(coords) != 3)
	{
		ft_strstr_free(coords);
		return ((t_vec3){{-0.0F, -0.0F, -0.0F}});
	}
	xyz.x = ft_check_float(coords[0], error, -FLT_MAX, FLT_MAX, line);
	xyz.y = ft_check_float(coords[1], error, -FLT_MAX, FLT_MAX, line);
	xyz.z = ft_check_float(coords[2], error, -FLT_MAX, FLT_MAX, line);
	ft_strstr_free(coords);
	if ((signbit(xyz.x) && xyz.x == 0.0f)
		|| (signbit(xyz.y) && xyz.y == 0.0f)
		|| (signbit(xyz.z) && xyz.z == 0.0f))
	{
		printf(B_RD_0"Line [%d]\tError in coordenates\n"RESET, line);
		(*error)++;
		return (xyz);
	}
	return (xyz);
}

void	ft_extact_ambient(t_image *image, char ***split, int *error, int line)
{
	if (ft_strstr_len(*split) != 3)
	{
		printf(B_RD_0 "Line [%d]\tFormato esperado 'A ratio [R,G,B]'" RESET "\n", line);
		(*error)++;
		return;
	}
	image->objects->ambient = ft_calloc(sizeof(t_ambient), 1);
	image->objects->ambient->ambient_light = ft_check_float((*split)[1], error, 0.0F, 1.0F, line);
	image->objects->ambient->color = ft_split_colors((*split)[2], error, line);
}

void	ft_extact_camera(t_image *image, char ***split, int *error, int line)
{
	if (ft_strstr_len(*split) != 4)
	{
		printf(B_RD_0 "Line [%d]\tFormato esperado 'C [x,y,z] [vector] FOV'" RESET "\n", line);
		(*error)++;
		return;
	}
	image->objects->camera = ft_calloc(sizeof(t_camera), 1);
	image->objects->camera->position = ft_split_coords((*split)[1], error, line);
	image->objects->camera->normal = ft_split_coords((*split)[2], error, line);
	image->objects->camera->fov = (int)ft_check_float((*split)[3], error, 0, 180, line);
}

void	ft_extact_light(t_image *image, char ***split, int *error, int line)
{
	if (ft_strstr_len(*split) != 4)
	{
		printf(B_RD_0 "Line [%d]\tFormato esperado 'L [x,y,z] ratio [R,G,B]'" RESET "\n", line);
		(*error)++;
		return;
	}
	image->objects->light = ft_calloc(sizeof(t_light), 1);
	image->objects->light->position = ft_split_coords((*split)[1], error, line);
	image->objects->light->brightness = ft_check_float((*split)[2], error, 0.0F, 1.0F, line);
	image->objects->light->color = ft_split_colors((*split)[3], error, line);
}

void	ft_extact_sphere(t_image *image, char ***split, int *error, int line)
{
	t_sphere	*new_sphere;

	if (ft_strstr_len(*split) != 4)
	{
		printf(B_RD_0 "Line [%d]\tFormato esperado 'sp [x,y,z] diam [R,G,B]'" RESET "\n", line);
		(*error)++;
		return;
	}
	new_sphere = ft_calloc(sizeof(t_sphere), 1);
	new_sphere->position = ft_split_coords((*split)[1], error, line);
	new_sphere->diameter = ft_check_float((*split)[2], error, 0.0F, FLT_MAX, line);
	new_sphere->color = ft_split_colors((*split)[3], error, line);
	new_sphere->radius = new_sphere->diameter / 2; 
	ft_lstadd_back_general((void **)&image->objects->sphere, new_sphere);
}

void	ft_extact_plane(t_image *image, char ***split, int *error, int line)
{
	t_plane	*new_plane;

	if (ft_strstr_len(*split) != 4)
	{
		printf(B_RD_0 "Line [%d]\tFormato esperado 'pl [x,y,z] [vector] [R,G,B]'" RESET "\n", line);
		(*error)++;
		return;
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

	if (ft_strstr_len(*split) != 6)
	{
		printf(B_RD_0 "Line [%d]\tFormato esperado 'cy [x,y,z] [vector] diam altura [R,G,B]'" RESET "\n", line);
		(*error)++;
		return;
	}
	new_cylinder = ft_calloc(sizeof(t_cylinder), 1);
	new_cylinder->position = ft_split_coords((*split)[1], error, line);
	new_cylinder->normal = ft_split_coords((*split)[2], error, line);
	new_cylinder->diameter = ft_check_float((*split)[3], error, 0.0F, FLT_MAX, line);
	new_cylinder->height = ft_check_float((*split)[4], error, 0.0F, FLT_MAX, line);
	new_cylinder->color = ft_split_colors((*split)[5], error, line);
	new_cylinder->radius = new_cylinder->diameter / 2; 
	ft_lstadd_back_general((void **)&image->objects->cylinder, new_cylinder);
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
	if (ft_strnstr(split[0], "A", 1) != NULL)
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
	t_image	*current_image;
	char	*content_clean;
	char	*content;
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
		ft_process_line(current_image, content_clean, &error, line++);
		free(content);
		free(content_clean);
		content = get_next_line(fd);
	}
	if (error != 0)
	{
		printf(B_WH_0"\n\t    ╭─────────────────────────────╮\n"RESET);
		printf(B_WH_0"\t    │ "B_BL_0"      Errors found: "B_PR_0"%d       "B_WH_0"│\n"RESET, error);
		printf(B_WH_0"\t    ╰─────────────────────────────╯\n\n"RESET);
		exit(1);
	}
}
