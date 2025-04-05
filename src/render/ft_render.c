/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:33:31 by descamil          #+#    #+#             */
/*   Updated: 2025/04/05 13:12:09 by descamil         ###   ########.fr       */
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

void ft_init_camera(t_image *image)
{
	t_camera	*camera;
	t_cam3		coord;
	t_vec3		half;
	float		viewport_width;
	float		viewport_height;

	camera = image->objects->camera;
	half = (t_vec3){{0.5, 0.5, 0.5}};
	image->aspect_ratio = (float)image->height / image->width;
	viewport_width = 2 * tan(camera->fov / 2);
	viewport_height = viewport_width * (float)image->aspect_ratio;	
	coord.w = ft_normalice(ft_multiply(camera->normal, (t_vec3){{-1, -1, -1}}));
	coord.u = ft_cross((t_vec3){{0, 1, 0}}, coord.w);
	coord.v = ft_cross(coord.w, coord.u);
	camera->horizontal = ft_multiply(coord.u, ft_float_to_vec3(viewport_width));
	camera->vertical = ft_multiply(coord.v, ft_float_to_vec3(viewport_height));
	camera->l_left_corner = ft_subtract(camera->position, ft_multiply(camera->horizontal, half));
	camera->l_left_corner = ft_subtract(camera->l_left_corner, ft_multiply(camera->vertical, half));
	camera->l_left_corner = ft_subtract(camera->l_left_corner, coord.w);
}

void	ft_create_render(t_mlx *data, t_image *image)
{
	t_vec3	color;
	t_vec2	coord;
	int		y;
	int		x;

	y = 0;
	ft_init_camera(image);
	while (y < image->height)
	{
		coord.y = (float)y / image->height;
		x = 0;
		while (x < image->width)
		{
			coord.x = (float)x / image->width;
			color = ft_per_pixel(image, coord);
			my_mlx_pixel_put(data, x, y, ft_convert_rgba(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
}
