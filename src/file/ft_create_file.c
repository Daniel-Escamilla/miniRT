/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:01:10 by descamil          #+#    #+#             */
/*   Updated: 2024/11/05 12:02:54 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

int	ft_nothing(char *input, int i)
{
	while (input[i] && input[i] == ' ' && input[i] == '\n')
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

t_vec3	ft_split_colors(char *line)
{
	t_vec3	rgb;
	int		ttf;
	char	**colors;

	colors = ft_split(line, ',');
	if (colors == NULL)
		return ((t_vec3){-1, -1, -1});
	if (colors[0])
	{
		ttf = ft_atoi(colors[0]);
		if (ttf < 0 || ttf > 255)
			ft_error("A --> Red not in range [0 - 255]", -1);
	}
	if (colors[1])
	{
		
	}
	if (colors[2])
	{
		
	}
}

void	ft_exrtact_ambient(t_image *image, char **split)
{
	char	**colors;
	float	atof;

	if (split[1])
	{
		atof = (ft_atof(split[1]));
		if (atof > 1.0f || atof < 0.0f)
			ft_error("A --> Ambient light not in range [0.0 - 1.0]", -1);
		image->objects->ambient->ambient_light = ft_atof(split[1]);
	}
	else
		ft_error("Ambient light missing", -1);
	if (split[2])
	{
		image->objects->ambient->color = ft_split_colors(split[2]);
		if (image->objects->ambient->color.r == -1 || image->objects->ambient->color.g == -1 ||image->objects->ambient->color.b == -1)
			ft_error("Color not in range [0,0,0 - 255,255,255]", -1);
	}
}

void	ft_exrtact_camera(t_image *image, char **split)
{
	
}

void	ft_exrtact_light(t_image *image, char **split)
{
	
}

void	ft_exrtact_sphere(t_image *image, char **split)
{
	
}

void	ft_exrtact_plane(t_image *image, char **split)
{
	
}

void	ft_exrtact_cylinder(t_image *image, char **split)
{
	
}


void	ft_process_line(t_image *image, char *line)
{
	char	**split;

	if (ft_noting(line, 0) == 1)
		return ;
	split = ft_split(line, ' ');
	if (ft_strnstr(split[0], "ACLspplcy", 10) == NULL)
		return ;
	else if (ft_strnstr(split[0], "A", 1) != NULL)
		ft_extact_ambient(image, split);
	else if (ft_strnstr(split[0], "C", 1) != NULL)
		ft_extact_camera(image, split);
	else if (ft_strnstr(split[0], "L", 1) != NULL)
		ft_extact_light(image, split);
	else if (ft_strnstr(split[0], "sp", 2) != NULL)
		ft_extact_sphere(image, split);
	else if (ft_strnstr(split[0], "pl", 2) != NULL)
		ft_extact_plane(image, split);
	else if (ft_strnstr(split[0], "cy", 2) != NULL)
		ft_extact_cylinder(image, split);
}

void	ft_create_struct(t_image *image, char **argv)
{
	char	*line;
	int		fd;

	fd = ft_open_file(argv);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_process_line(image, line);
		free(line);
		line = get_next_line(fd);
	}
	// ft_fill_in(image);
}