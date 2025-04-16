/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:36:30 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:36:31 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minirt.h"

// ft_normalice_values.c
void	ft_normalice_planes(t_plane *plane);
void	ft_normalice_cylinders(t_cylinder *cylinder);
t_vec3	ft_normalice_camera(t_vec3 v);
void	ft_normalice_values(t_image *image);

// ft_window.c
int		ft_end_program(t_image *image);
void	ft_create_window(t_mlx *data, t_image *image);

// ft_main.c
int		ft_hooks(int key, t_image *image);
void	ft_initialize(t_image *image);
int		main(int argc, char **argv);

#endif
