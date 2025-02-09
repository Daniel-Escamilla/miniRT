/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:02:54 by descamil          #+#    #+#             */
/*   Updated: 2025/01/21 14:48:38 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minirt.h"

// ft_initialize.c
void	ft_initialize(t_image *image);

// ft_window.c
int		ft_end_program(t_image *image);
void	ft_create_window(t_mlx *data, t_image *image);

#endif
