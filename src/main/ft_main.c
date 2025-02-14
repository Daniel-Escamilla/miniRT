/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:57:18 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 21:37:02 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int main(int argc, char **argv)
{
	t_image image;

	(void) argc;
	(void) argv;
	ft_initialize(&image);

	if (ft_file_exist(argv, argc) == -1)
		return (-1);
	ft_create_struct(&image, argv);
	ft_create_window(image.data, &image);
	print_objects(image.objects);
	// mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);
	// mlx_loop(image.mlx);
	ft_free_all(&image);
	return (0);
}
