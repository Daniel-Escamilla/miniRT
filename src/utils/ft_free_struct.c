/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:29:01 by descamil          #+#    #+#             */
/*   Updated: 2025/02/14 21:37:38 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static void ft_safe_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_list_general(void **list)
{
	void	*current;
	void	*next;

	if (!list || !*list)
		return ;
	current = *list;
	while (current != NULL)
	{
		next = *(void **)current;
		free(current);
		current = next;
	}
	list = NULL;
}

void	ft_free_all(t_image *image)
{
	if (image->objects)
	{
		ft_safe_free((void **)&image->objects->ambient);
		ft_safe_free((void **)&image->objects->camera);
		ft_safe_free((void **)&image->objects->light);
		ft_free_list_general((void **)&image->objects->sphere);
		ft_free_list_general((void **)&image->objects->plane);
		ft_free_list_general((void **)&image->objects->cylinder);
		ft_safe_free((void **)&image->objects);
	}
	if (image->data)
	{
		if (image->data->img)
			mlx_destroy_image(image->mlx, image->data->img);
		ft_safe_free((void **)&image->data);
	}
	if (image->mlx_win)
		mlx_destroy_window(image->mlx, image->mlx_win);
	ft_safe_free((void **)&image->mlx);
}
