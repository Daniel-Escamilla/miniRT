/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:33:31 by descamil          #+#    #+#             */
/*   Updated: 2025/04/04 16:36:20 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_convert_rgba(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.x * 255.0f);
	g = (int)(color.y * 255.0f);
	b = (int)(color.z * 255.0f);
	return ((r << 16) | (g << 8) | b);
}

// t_vec3	ft_per_pixel(t_image *image, t_vec2 coord)
// {
// 	t_vec3	color;
// 	(void)image;

// 	float dist = sqrtf(coord.x * coord.x + coord.y * coord.y);
// 	if (dist > 1.0f)
// 		dist = 1.0f;

// 	if (dist <= 0.5f)
// 	{
// 		color.x = 0.0f;               // red
// 		color.y = dist * 2.0f;        // green sube hasta 1
// 		color.z = 0.0f;               // blue
// 	}
// 	else
// 	{
// 		color.x = (dist - 0.5f) * 2.0f; // red sube de 0 a 1
// 		color.y = 1.0f - (dist - 0.5f) * 2.0f; // green baja de 1 a 0
// 		color.z = 0.0f;                 // blue
// 	}

// 	return (color);
// }

void	ft_create_render(t_mlx *data, t_image *image)
{
	t_vec3	color;
	t_vec2	coord;
	int		y;
	int		x;

	y = 0;
	while (y < image->height)
	{
		coord.y = 1.0f - ((float)y / (float)image->height) * 2.0f;
		x = 0;
		while (x < image->width)
		{
			coord.x = ((float)x / (float)image->width) * 2.0f - 1.0f;
			color = ft_per_pixel(image, coord);
			my_mlx_pixel_put(data, x, y, ft_convert_rgba(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
}
