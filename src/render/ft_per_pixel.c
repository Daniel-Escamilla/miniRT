/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_per_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:29:21 by descamil          #+#    #+#             */
/*   Updated: 2025/04/04 15:59:28 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	ft_init_values()
{
	
}

t_vec3	ft_per_pixel(t_image *image, t_vec2 coord)
{
	ft_init_values(image);
	(void)image;
	(void)coord;
	return ((t_vec3){{1.0f, 0.0f, 0.5f}});
}
