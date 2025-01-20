/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:37:54 by descamil          #+#    #+#             */
/*   Updated: 2024/12/19 11:36:50 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minirt.h"

// ft_atof.c
float	ft_atof(char *str);

// ft_atoi_mod.c
int		ft_atoi_mod(char *str, int *error);

// ft_strstr_utils.c
int		ft_strstr_len(char **str);
void	ft_strstr_free(char **str);
char	**ft_strstr_dup(char **str);
int		ft_strnstrstr(char **str, char *locate);
char	**ft_strstr_join(char **str, char **str1);

#endif