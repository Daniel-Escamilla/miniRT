/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:09:02 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 20:01:00 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../minirt.h"
# include "objects_struct.h"
# include "math_struct.h"

// MLX_STRUCT
typedef struct s_mlx
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;

// IMAGE_STRUCT
typedef struct s_image
{
	t_objects	*objects;
	t_mlx		*data;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	float		aspect_ratio;
}				t_image;

#endif
