/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:07:02 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/21 10:18:45 by stescaro         ###   ########.fr       */
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

void	free_imgs(t_imgs *imgs, void *mlx)
{
	if (imgs->wall)
		mlx_destroy_image(mlx, imgs->wall);
	if (imgs->floor)
		mlx_destroy_image(mlx, imgs->floor);
	if (imgs->player)
		mlx_destroy_image(mlx, imgs->player);
	if (imgs->door)
		mlx_destroy_image(mlx, imgs->door);
	if (imgs->empty)
		mlx_destroy_image(mlx, imgs->empty);
	if (imgs->n_wall)
		mlx_destroy_image(mlx, imgs->n_wall);
	if (imgs->s_wall)
		mlx_destroy_image(mlx, imgs->s_wall);
	if (imgs->w_wall)
		mlx_destroy_image(mlx, imgs->w_wall);
	if (imgs->e_wall)
		mlx_destroy_image(mlx, imgs->e_wall);
	free(imgs);
}

int	ft_freedata(t_data *data)
{
	if (data->position)
		free(data->position);
	if (data->texture)
		free_texture(data->texture);
	if (data->imgs)
		free_imgs(data->imgs, data->window->mlx);
	if (data->window)
		free_window(data->window);
	if (data->map)
	{
		if (data->map->map)
			ft_freesplit(data->map->map);
		free(data->map);
	}
	free(data);
	return (1);
}
