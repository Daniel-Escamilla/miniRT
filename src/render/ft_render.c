/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:33:31 by descamil          #+#    #+#             */
/*   Updated: 2025/04/13 18:05:20 by descamil         ###   ########.fr       */
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

	// Asegurarse de que los valores estén en el rango 0-255
	r = (int)(color.r < 0 ? 0 : (color.r > 255 ? 255 : color.r));
	g = (int)(color.g < 0 ? 0 : (color.g > 255 ? 255 : color.g));
	b = (int)(color.b < 0 ? 0 : (color.b > 255 ? 255 : color.b));

	return ((r << 16) | (g << 8) | b);
}


// void ft_init_camera(t_image *image)
// {
// 	t_camera	*camera;
// 	t_cam3		coord;
// 	t_vec3		half;
// 	double		viewport_width;
// 	double		viewport_height;

// 	camera = image->objects->camera;
// 	half = (t_vec3){{0.5, 0.5, 0.5}};
// 	image->aspect_ratio = (double)image->height / image->width;
// 	viewport_width = 2 * tan(camera->fov / 2);
// 	viewport_height = viewport_width * (double)image->aspect_ratio;
// 	coord.w = ft_normalice(ft_scale(camera->normal, -1));
// 	coord.u = ft_cross((t_vec3){{0, 1, 0}}, coord.w);
// 	coord.v = ft_cross(coord.w, coord.u);
// 	camera->horizontal = ft_scale(coord.u, viewport_width);
// 	camera->vertical = ft_scale(coord.v, viewport_height);
// 	camera->l_left_corner = ft_subtract(camera->position, ft_multiply(camera->horizontal, half));
// 	camera->l_left_corner = ft_subtract(camera->l_left_corner, ft_multiply(camera->vertical, half));
// 	camera->l_left_corner = ft_subtract(camera->l_left_corner, coord.w);
// }

void ft_init_camera(t_image *image)
{
    t_camera *camera;
    t_cam3 coord;
    t_vec3 half;
    double viewport_width;
    double viewport_height;

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
    camera->l_left_corner = ft_subtract(camera->position, ft_multiply(camera->horizontal, half));
    camera->l_left_corner = ft_subtract(camera->l_left_corner, ft_multiply(camera->vertical, half));
    camera->l_left_corner = ft_subtract(camera->l_left_corner, coord.w);
}

#include <pthread.h>

typedef struct s_thread_data {
    t_mlx		*data;
    t_image		*image;
    int			start_y;
    int			end_y;
} t_thread_data;

void	*ft_render_thread(void *arg)
{
    t_thread_data	*thread_data = (t_thread_data *)arg;
    t_vec3			color;
    t_vec2			coord;
    int				y;
    int				x;
    int				result;

    y = thread_data->start_y;
    while (y < thread_data->end_y)
    {
        coord.y = (double)y / thread_data->image->height;
        x = 0;
        while (x < thread_data->image->width)
        {
            coord.x = (double)x / thread_data->image->width;
            color = ft_per_pixel(thread_data->image, coord);
            result = ft_convert_rgba(color);
            my_mlx_pixel_put(thread_data->data, x, thread_data->image->height - y - 1, result);
            x++;
        }
        y++;
    }
    return (NULL);
}

void	ft_create_render(t_mlx *data, t_image *image)
{
    const int		num_threads = 4; // Número de hilos
    pthread_t		threads[num_threads];
    t_thread_data	thread_data[num_threads];
    int				i;
    int				rows_per_thread;

    ft_init_camera(image);
    rows_per_thread = image->height / num_threads;

    // Crear hilos
    for (i = 0; i < num_threads; i++)
    {
        thread_data[i].data = data;
        thread_data[i].image = image;
        thread_data[i].start_y = i * rows_per_thread;
        thread_data[i].end_y = (i == num_threads - 1) ? image->height : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, ft_render_thread, &thread_data[i]);
    }

    // Esperar a que los hilos terminen
    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
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
// 		int	result = 0;
// 		while (x < image->width)
// 		{
// 			coord.x = (double)x / image->width;
// 			color = ft_per_pixel(image, coord);
// 			result = ft_convert_rgba(color);
// 			my_mlx_pixel_put(data, x, image->height - y - 1, result);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(image->mlx, image->mlx_win, data->img, 0, 0);
// }
