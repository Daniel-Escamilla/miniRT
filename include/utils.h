/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:35:06 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:46:58 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minirt.h"

// ft_free_struct.c
void	ft_safe_free(void **ptr);
void	ft_free_list_general(void **list);
void	ft_free_all(t_image *image);

// ft_atof.c
double	convert_integer_part(char *str, int *i, int *error);
double	convert_decimal_part(char *str, int *i, int *error);
int		ft_all_numbers(char *str);
double	ft_atof(char *str);

// ft_atoi_mod.c
int		calculate_result(char *str, int *i, int *error, int sign);
int		ft_atoi_mod(char *str, int *error);

// ft_strstr_utils.c
int		ft_strnstrstr(char **str, char *locate);
int		ft_strstr_len(char **str);
void	ft_strstr_free(char **str);

#endif
