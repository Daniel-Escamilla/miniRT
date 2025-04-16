/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:20 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:48:04 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

double	ft_check_float(char *split, int *error, t_vec2 limit, int line)
{
	double	atof;

	atof = ft_atof(split);
	if (atof < limit.min || atof > limit.max
		|| (signbit(atof) && atof == -0.0F))
	{
		if (limit.min == -FLT_MAX && limit.max == FLT_MAX)
			printf(B_RD_0"Line [%d]\t%f not in range"
				" [{-FLT_MAX} - {FLT_MAX}]\n"RESET, line, atof);
		else if (limit.max == FLT_MAX)
			printf(B_RD_0"Line [%d]\t%f not in range"
				" [{%f} - {FLT_MAX}]\n"RESET, line, atof, limit.min);
		else
			printf(B_RD_0"Line [%d]\t%f not in range"
				" [%f - %f]\n"RESET, line, atof, limit.min, limit.max);
		(*error)++;
	}
	return (atof);
}

t_vec3	ft_split_colors(char *color, int *error, int line)
{
	t_vec3	rgb;
	t_vec2	limit;
	char	**colors;

	colors = ft_split(color, ',');
	if (ft_strstr_len(colors) != 3)
	{
		(*error)++;
		printf(B_RD_0"Line [%d]\tColors not set\n"RESET, line);
		return ((t_vec3){{-1, -1, -1}});
	}
	limit.min = 0;
	limit.max = 255;
	rgb.r = (int)ft_check_float(colors[0], error, limit, line);
	rgb.g = (int)ft_check_float(colors[1], error, limit, line);
	rgb.b = (int)ft_check_float(colors[2], error, limit, line);
	ft_strstr_free(colors);
	return (rgb);
}

t_vec3	ft_split_coords(char *coord, int *error, int line)
{
	t_vec3	xyz;
	t_vec2	limit;
	char	**coords;

	coords = ft_split(coord, ',');
	if (ft_strstr_len(coords) != 3)
	{
		ft_strstr_free(coords);
		return ((t_vec3){{-0.0F, -0.0F, -0.0F}});
	}
	limit.min = -FLT_MAX;
	limit.max = FLT_MAX;
	xyz.x = ft_check_float(coords[0], error, limit, line);
	xyz.y = ft_check_float(coords[1], error, limit, line);
	xyz.z = ft_check_float(coords[2], error, limit, line);
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

int	ft_check_identifier(char *ident, int *error, char **split, int line)
{
	if (ft_strncmp(ident, "A", 2) == 0)
		return (0);
	if (ft_strncmp(ident, "C", 2) == 0)
		return (0);
	if (ft_strncmp(ident, "L", 2) == 0)
		return (0);
	if (ft_strncmp(ident, "sp", 3) == 0)
		return (0);
	if (ft_strncmp(ident, "pl", 3) == 0)
		return (0);
	if (ft_strncmp(ident, "cy", 3) == 0)
		return (0);
	*error += 1;
	printf(B_RD_0 "Line [%d]\t%s\tExpected: A, L, C,"
		" sp, pl, cy" RESET "\n", line, split[0]);
	ft_strstr_free(split);
	return (1);
}
