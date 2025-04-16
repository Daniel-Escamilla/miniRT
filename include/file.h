/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:34:14 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:34:15 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "../minirt.h"

// ft_extract_objects.c
void	ft_extact_sphere(t_image *image, char ***split, int *error, int line);
void	ft_extact_plane(t_image *image, char ***split, int *error, int line);
void	ft_extact_cylinder(t_image *image, char ***split, int *error, int line);

// ft_extract_values.c
double	ft_check_float(char *split, int *error, t_vec2 limit, int line);
t_vec3	ft_split_colors(char *color, int *error, int line);
t_vec3	ft_split_coords(char *coord, int *error, int line);
int		ft_check_identifier(char *ident, int *error, char **split, int line);

// ft_open_file.c
int		ft_open_file(char **argv);

// ft_extract_lines.c
void	ft_extact_ambient(t_image *image, char ***split, int *error, int line);
void	ft_extact_camera(t_image *image, char ***split, int *error, int line);
void	ft_extact_light(t_image *image, char ***split, int *error, int line);

// ft_create_file.c
void	ft_lstadd_back_general(void **list, void *new);
int		ft_nothing(const char *input, int i);
void	ft_process_line(t_image *image, char *content, int *error, int line);
int		ft_print_error(int error);
void	ft_create_struct(t_image *image, char **argv);

// ft_file_exist.c
int		ft_error(char *file, char *error, int status);
int		ft_file_exist(char **argv, int argc);

#endif
