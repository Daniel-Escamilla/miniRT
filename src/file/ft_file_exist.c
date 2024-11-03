/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:14:04 by descamil          #+#    #+#             */
/*   Updated: 2024/11/02 22:38:17 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

int	ft_error(char *error, int status)
{
	printf("%s\n", error);
	return (status);
}

int	ft_file_exist(char **argv, int argc)
{
	char	*file;

	if (argc != 2)
		return (ft_error("./minirt {file.rt}", -1));
	file = ft_strrchr(argv[1], '.');
	if (file == NULL)
		return (ft_error("Add to file --> [.]rt", -1));
	if (ft_strncmp(file, argv[1], ft_strlen(argv[1])) == 0
		&& ft_strncmp(argv[1], file, ft_strlen(file)) == 0)
		return (ft_error("Add [file] to --> .", -1));
	file = ft_strnstr(file, ".rt", 3);
	if (file == NULL || ft_strlen(file) != 3)
		return (ft_error("Add to file --> [rt]", -1));
	if (access(argv[1], F_OK) == -1)
		return (ft_error("Create file.rt", -1));
	if (access(argv[1], R_OK) == -1)
		return (ft_error("Give permissions to {file.rt}\n"
			"\n\tchmod +r {file.rt}\n", -1));
	return (0);
}
