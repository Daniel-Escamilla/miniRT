/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:37:54 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 21:37:45 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minirt.h"

// ft_atof.c
double	ft_atof(char *str);

// ft_atoi_mod.c
int		ft_atoi_mod(char *str, int *error);

// ft_print_struct.c
void	print_objects(t_objects *objects);
void	print_vec3(t_vec3 vec);

// ft_free_struct.c
void	ft_free_all(t_image *image);
void	ft_free_list_general(void **list);

// ft_strstr_utils.c
int		ft_strstr_len(char **str);
void	ft_strstr_free(char **str);
char	**ft_strstr_dup(char **str);
int		ft_strnstrstr(char **str, char *locate);
char	**ft_strstr_join(char **str, char **str1);

#endif
