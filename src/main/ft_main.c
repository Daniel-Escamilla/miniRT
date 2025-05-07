/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:57:18 by descamil          #+#    #+#             */
/*   Updated: 2025/05/07 11:58:07 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	ft_hooks(int key, t_image *image)
{
	if (key == 65307)
		ft_end_program(image);
	return (0);
}

void	ft_initialize(t_image *image)
{
	image->data = ft_calloc(sizeof(t_mlx), 1);
	image->width = 800;
	image->height = 800;
	image->objects = ft_calloc(sizeof(t_objects), 1);
}

int	main(int argc, char **argv)
{
	t_image	image;

	if (ft_file_exist(argv, argc) == -1)
		return (-1);
	ft_initialize(&image);
	ft_create_struct(&image, argv);
	ft_create_window(image.data, &image);
	ft_normalice_values(&image);
	ft_create_render(image.data, &image);
	mlx_key_hook(image.mlx_win, ft_hooks, &image);
	mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);
	mlx_loop(image.mlx);
	ft_free_all(&image);
	return (0);
}
