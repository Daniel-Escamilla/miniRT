/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:09:33 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:09:55 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

int	check_rgb(int color)
{
	if (color > 255)
		return (255);
	if (color < 0)
		return (0);
	return (color);
}

t_vec3	ft_scale_color(t_vec3 color, double f)
{
	t_vec3	rgb;

	rgb.r = check_rgb(f * color.r);
	rgb.g = check_rgb(f * color.g);
	rgb.b = check_rgb(f * color.b);
	return (rgb);
}

t_vec3	ft_adjust_color(t_vec3 color, t_vec3 adjuster)
{
	t_vec3	rgb;

	rgb.r = check_rgb(((color.r / 255.0f) * (adjuster.r / 255.0f)) * 255.0f);
	rgb.g = check_rgb(((color.g / 255.0f) * (adjuster.g / 255.0f)) * 255.0f);
	rgb.b = check_rgb(((color.b / 255.0f) * (adjuster.b / 255.0f)) * 255.0f);
	return (rgb);
}
