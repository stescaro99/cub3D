/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:07:02 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/14 15:11:13 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	free_window(t_window *window)
{
	if (window->win)
		mlx_destroy_window(window->mlx, window->win);
	if (window->mlx)
	{
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
	free(window);
}

static	void	free_texture(t_texture *texture)
{
	if (texture->no)
		free(texture->no);
	if (texture->so)
		free(texture->so);
	if (texture->we)
		free(texture->we);
	if (texture->ea)
		free(texture->ea);
	if (texture->celing)
		free(texture->celing);
	if (texture->floor)
		free(texture->floor);
	free(texture);
}

int	ft_freedata(t_data *data)
{
	if (data->map)
		ft_freesplit(data->map);
	if (data->position)
		free(data->position);
	if (data->texture)
		free_texture(data->texture);
	if (data->window)
		free_window(data->window);
	free(data);
	return (1);
}
