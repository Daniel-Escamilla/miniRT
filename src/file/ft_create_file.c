/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:01:10 by descamil          #+#    #+#             */
/*   Updated: 2024/11/03 12:33:40 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

int	ft_nothing(char *input, int i)
{
	while (input[i] && input[i] == ' ' && input[i] == '\n')
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

void	ft_exrtact_info(t_image *image, char **split, int type)
{
	
}

void	ft_process_line(t_image *image, char *line)
{
	char	**split;

	if (ft_noting(line, 0) == 1)
		return ;
	split = ft_split(line, ' ');
	if (ft_strnstr(split[0], "ACLspplcy", 10) == NULL)
		return ;
	else if (ft_strnstr(split[0], "A", 1) != NULL)
		ft_extact_info(image, split, AMBIENT);
	else if (ft_strnstr(split[0], "C", 1) != NULL)
		ft_extact_info(image, split, CAMERA);
	else if (ft_strnstr(split[0], "L", 1) != NULL)
		ft_extact_info(image, split, LIGHT);
	else if (ft_strnstr(split[0], "sp", 2) != NULL)
		ft_extact_info(image, split, SPHERE);
	else if (ft_strnstr(split[0], "pl", 2) != NULL)
		ft_extact_info(image, split, PLANE);
	else if (ft_strnstr(split[0], "cy", 2) != NULL)
		ft_extact_info(image, split, CYLINDER);
}

void	ft_create_struct(t_image *image, char **argv)
{
	char	*line;
	int		fd;

	fd = ft_open_file(argv);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_process_line(image, line);
		free(line);
		line = get_next_line(fd);
	}
	// ft_fill_in(image);
}