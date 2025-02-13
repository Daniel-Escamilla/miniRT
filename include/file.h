/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:02:02 by descamil          #+#    #+#             */
/*   Updated: 2025/02/13 18:43:21 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

#include "../minirt.h"

// ft_create_file.c
int		ft_nothing(char *input, int i);
void	ft_create_struct(t_image *image, char **argv);
void	ft_free_list_general(void **list);

// ft_open_file.c
int		ft_open_file(char **argv);

// ft_file_exist.c
// int		ft_error(char *error, int status);
int		ft_file_exist(char **argv, int argc);
int		ft_error(char *file, char *error, int status);

#endif
