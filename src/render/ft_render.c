/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:33:31 by descamil          #+#    #+#             */
/*   Updated: 2025/06/14 13:04:29 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_convert_rgba(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)color.r;
	g = (int)color.g;
	b = (int)color.b;
	if (color.r < 0)
		r = 0;
	else if (color.r > 255)
		r = 255;
	if (color.g < 0)
		g = 0;
	else if (color.g > 255)
		g = 255;
	if (color.b < 0)
		b = 0;
	else if (color.b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

void	ft_init_camera(t_image *image)
{
	t_camera	*camera;
	t_cam3		coord;
	t_vec3		half;
	double		viewport_width;
	double		viewport_height;

	camera = image->objects->camera;
	half = (t_vec3){{0.5, 0.5, 0.5}};
	image->aspect_ratio = (double)image->height / image->width;
	viewport_width = 2 * tan(camera->fov / 2);
	viewport_height = viewport_width * (double)image->aspect_ratio;
	coord.w = ft_normalice(ft_scale(camera->normal, -1));
	coord.u = ft_cross((t_vec3){{0, 1, 0}}, coord.w);
	coord.v = ft_cross(coord.w, coord.u);
	camera->horizontal = ft_scale(coord.u, viewport_width);
	camera->vertical = ft_scale(coord.v, viewport_height);
	camera->l_left_corner = ft_sub(camera->position,
			ft_mult(camera->horizontal, half));
	camera->l_left_corner = ft_sub(camera->l_left_corner,
			ft_mult(camera->vertical, half));
	camera->l_left_corner = ft_sub(camera->l_left_corner, coord.w);
}

// void	ft_create_render(t_mlx *data, t_image *image)
// {
// 	t_vec3	color;
// 	t_vec2	coord;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	ft_init_camera(image);
// 	while (y < image->height)
// 	{
// 		coord.y = (double)y / image->height;
// 		x = 0;
// 		while (x < image->width)
// 		{
// 			coord.x = (double)x / image->width;
// 			color = ft_per_pixel(image, coord);
// 			my_mlx_pixel_put(data, x, image->height - y - 1,
// 				ft_convert_rgba(color));
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
// }


#include <pthread.h>

#define THREAD_COUNT 8

typedef struct s_thread_data {
	t_mlx		*data;
	t_image		*image;
	int			start_y;
	int			end_y;
}	t_thread_data;

void	*ft_render_slice(void *arg)
{
	t_thread_data	*td = (t_thread_data *)arg;
	t_vec3			color;
	t_vec2			coord;
	int				x, y;

	y = td->start_y;
	while (y < td->end_y)
	{
		coord.y = (double)y / td->image->height;
		x = 0;
		while (x < td->image->width)
		{
			coord.x = (double)x / td->image->width;
			color = ft_per_pixel(td->image, coord);
			my_mlx_pixel_put(td->data, x, td->image->height - y - 1,
				ft_convert_rgba(color));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	ft_create_render(t_mlx *data, t_image *image)
{
	pthread_t		threads[THREAD_COUNT];
	t_thread_data	td[THREAD_COUNT];
	int				i;
	int				slice;

	ft_init_camera(image);
	slice = image->height / THREAD_COUNT;
	i = 0;
	while (i < THREAD_COUNT)
	{
		td[i].data = data;
		td[i].image = image;
		td[i].start_y = i * slice;
		td[i].end_y = (i == THREAD_COUNT - 1) ? image->height : (i + 1) * slice;
		pthread_create(&threads[i], NULL, ft_render_slice, &td[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
		pthread_join(threads[i++], NULL);
	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
}
