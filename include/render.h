/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:33:49 by descamil          #+#    #+#             */
/*   Updated: 2025/04/04 15:55:44 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../minirt.h"

// ft_maths.c
t_vec3	ft_normalice(t_vec3 vec);
float	ft_dot(t_vec3 a, t_vec3 b);

// ft_render.c
void	ft_create_render(t_mlx *data, t_image *image);

// ft_per_pixel.c
t_vec3	ft_per_pixel(t_image *image, t_vec2 coord);

#endif
