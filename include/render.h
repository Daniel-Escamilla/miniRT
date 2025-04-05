/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:33:49 by descamil          #+#    #+#             */
/*   Updated: 2025/04/05 12:43:37 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../minirt.h"

// ft_maths.c
t_vec3	ft_normalice(t_vec3 vec);
t_vec3	ft_float_to_vec3(float a);
float	ft_dot(t_vec3 a, t_vec3 b);
t_vec3	ft_cross(t_vec3 a, t_vec3 b);


// ft_render.c
void	ft_create_render(t_mlx *data, t_image *image);

// ft_operations.c
t_vec3	ft_add(t_vec3 a, t_vec3 b);
t_vec3	ft_divide(t_vec3 a, t_vec3 b);
t_vec3	ft_multiply(t_vec3 a, t_vec3 b);
t_vec3	ft_subtract(t_vec3 a, t_vec3 b);

// ft_per_pixel.c
t_vec3	ft_per_pixel(t_image *image, t_vec2 coord);

#endif
