/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:06:51 by descamil          #+#    #+#             */
/*   Updated: 2024/12/19 10:11:58 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

int	ft_open_file(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(argv[1], "Error open file.rt", -1);
	return (fd);
}
