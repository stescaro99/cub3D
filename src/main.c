/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:18:13 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/21 10:24:29 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_imgs	*set_img(void *mlx, t_texture *texture, t_data *data, int i)
{
	t_imgs	*img;

	img = ft_calloc(sizeof(t_imgs), 1);
	img->wall = mlx_xpm_file_to_image(mlx, "imgs/wall.xpm", &i, &i);
	img->floor = mlx_xpm_file_to_image(mlx, "imgs/floor.xpm", &i, &i);
	img->player = mlx_xpm_file_to_image(mlx, "imgs/player.xpm", &i, &i);
	img->door = mlx_xpm_file_to_image(mlx, "imgs/door.xpm", &i, &i);
	img->empty = mlx_xpm_file_to_image(mlx, "imgs/empty.xpm", &i, &i);
	if (!img->wall || !img->floor || !img->player || !img->door || !img->empty)
		return (perror("Error\nMinimap's images allocation failed"),
			free_imgs(img, mlx), ft_closegame(data), NULL);
	i = 200;
	img->n_wall = mlx_xpm_file_to_image(mlx, texture->no, &i, &i);
	if (!img->n_wall && ft_perror("Error\nWrong path: Northern wall"))
		return (free_imgs(img, mlx), ft_closegame(data), NULL);
	img->s_wall = mlx_xpm_file_to_image(mlx, texture->so, &i, &i);
	if (!img->s_wall && ft_perror("Error\nWrong path: Southern wall"))
		return (free_imgs(img, mlx), ft_closegame(data), NULL);
	img->w_wall = mlx_xpm_file_to_image(mlx, texture->we, &i, &i);
	if (!img->w_wall && ft_perror("Error\nWrong path: Western wall"))
		return (free_imgs(img, mlx), ft_closegame(data), NULL);
	img->e_wall = mlx_xpm_file_to_image(mlx, texture->ea, &i, &i);
	if (!img->e_wall && ft_perror("Error\nWrong path: Eastern wall"))
		return (free_imgs(img, mlx), ft_closegame(data), NULL);
	return (img);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (perror("Error\nWrong number of arguments"), 1);
	data = ft_calloc(sizeof(t_data), 1);
	if (check_map(argv[1], &(data->texture), &(data->map), &data))
		return (ft_freedata(data));
	data->window = ft_calloc(sizeof(t_window), 1);
	data->window->mlx = mlx_init();
	if (!data->window->mlx)
		return (perror("Error\nmlx_init failed"), ft_freedata(data));
	data->window->win = mlx_new_window(data->window->mlx, 1600, 900, "cub3d");
	if (!data->window->win)
		return (perror("Error\nmlx_new_window failed"), ft_freedata(data));
	data->imgs = set_img(data->window->mlx, data->texture, data, 5);
	cub3d(data);
	return (0);
}
