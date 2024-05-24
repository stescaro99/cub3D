/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:29:10 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/24 14:58:07 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*find_img_ptr(t_imgs *img, t_map *map, short x, short y)
{
	if (map->height <= y || map->lenght <= x || x < 0 || y < 0
		|| (short)ft_strlen(map->map[y]) <= x || !map->map[y][x]
		|| map->map[y][x] == ' ')
		return (img->empty);
	else if (map->map[y][x] == '1' || map->map[y][x] == 'w')
		return (img->wall);
	else if (map->map[y][x] == 'D')
		return (img->door);
	else if (map->map[y][x] == '0')
		return (img->floor);
	else if (ft_strchr("NSWE", map->map[y][x]))
		return (img->player);
	return (img->empty);
}

void	display_minimap(t_data *data, t_imgs *img)
{
	short	start_x;
	short	start_y;
	short	x;
	short	y;
	void	*img_ptr;

	start_x = (data->position->x - 12);
	start_y = (data->position->y - 7);
	y = start_y;
	while (y < start_y + 15)
	{
		x = start_x;
		while (x < start_x + 25)
		{
			img_ptr = find_img_ptr(img, data->map, x, y);
			mlx_put_image_to_window(data->window->mlx, data->window->win,
				img_ptr, 1300 + (x - start_x) * 10,
				700 + (y - start_y) * 10);
			x++;
		}
		y++;
	}
}
