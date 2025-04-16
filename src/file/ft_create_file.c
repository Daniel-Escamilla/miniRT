/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:01:10 by descamil          #+#    #+#             */
/*   Updated: 2025/04/16 12:00:17 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"

void	ft_lstadd_back_general(void **list, void *new)
{
	void	*current;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (*(void **)current != NULL)
		current = *(void **)current;
	*(void **)current = new;
}

int	ft_nothing(const char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\n'))
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

void	ft_process_line(t_image *image, char *content, int *error, int line)
{
	t_image	*current;
	char	**split;

	current = image;
	if (ft_nothing(content, 0) == 1)
		return ;
	split = ft_split(content, ' ');
	if (split == NULL)
		return ;
	if (ft_check_identifier(split[0], error, split, line))
		return ;
	if (ft_strnstr(split[0], "A", 1) != NULL)
		ft_extact_ambient(current, &split, error, line);
	else if (ft_strnstr(split[0], "C", 1) != NULL && ft_strlen(split[0]) == 1)
		ft_extact_camera(current, &split, error, line);
	else if (ft_strnstr(split[0], "L", 1) != NULL && ft_strlen(split[0]) == 1)
		ft_extact_light(current, &split, error, line);
	else if (ft_strnstr(split[0], "sp", 2) != NULL && ft_strlen(split[0]) == 2)
		ft_extact_sphere(current, &split, error, line);
	else if (ft_strnstr(split[0], "pl", 2) != NULL && ft_strlen(split[0]) == 2)
		ft_extact_plane(current, &split, error, line);
	else if (ft_strnstr(split[0], "cy", 2) != NULL && ft_strlen(split[0]) == 2)
		ft_extact_cylinder(current, &split, error, line);
	ft_strstr_free(split);
}

int	ft_print_error(int error)
{
	printf(B_WH_0"\n\t    ╭─────────────────────────────╮\n"RESET);
	printf(B_WH_0"\t    │ "B_BL_0"      Errors "
		"found: "B_PR_0"%d       "B_WH_0"│\n"RESET, error);
	printf(B_WH_0"\t    ╰─────────────────────────────╯\n\n"RESET);
	return (1);
}

void	ft_create_struct(t_image *image, char **argv)
{
	char	*content_clean;
	char	*content;
	int		error;
	int		line;
	int		fd;

	error = 0;
	line = 1;
	fd = ft_open_file(argv);
	if (fd == -1)
		return ;
	content = get_next_line(fd);
	while (content != NULL)
	{
		content_clean = ft_strtrim(content, "\n");
		ft_process_line(image, content_clean, &error, line++);
		free(content);
		free(content_clean);
		content = get_next_line(fd);
	}
	if (error != 0)
		exit(ft_print_error(error));
}
