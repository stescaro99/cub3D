/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:29:10 by stescaro          #+#    #+#             */
/*   Updated: 2024/06/04 16:01:00 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_minimap_color(short x, short y, t_data *data)
{
	float	x_mm;
	float	y_mm;
	char	tile;
	int		crd[2];
	void	*img;

	x_mm = (x - (short)(X_PIXEL * 4 / 5)) / 10 - (int)(X_PIXEL / 128);
	y_mm = (y - (short)(X_PIXEL * 9 / 20)) / 10 - (int)(X_PIXEL * 9 / 2048);
	crd[0] = (int)(data->position->x) + (int)x_mm + (x_mm > 1) * ((int)(x_mm
				* 10) % 10 != 0) - (x_mm < 1) * ((int)(x_mm * 10) % 10 != 0);
	crd[1] = (int)(data->position->y) + (int)(y_mm) + (y_mm > 1) * ((int)(y_mm
				* 10) % 10 != 0) - (y_mm < 1) * ((int)(y_mm * 10) % 10 != 0);
	if (crd[1] >= 0 && crd[1] < data->map->height && crd[0] >= 0
		&& crd[0] < (int)ft_strlen(data->map->map[crd[1]]))
		tile = data->map->map[crd[1]][crd[0]];
	else
		tile = 0;
	img = find_img_ptr(data->imgs, tile);
	return (get_pixel_color(img, (int)(x_mm * 10) % 10, (int)(y_mm * 10) % 10));
}

short	is_minimap(short x, short y, short x_pxl, short y_pxl)
{
	short	start_x;
	short	start_y;
	short	end_x;
	short	end_y;

	start_x = (short)(x_pxl * 4 / 5);
	start_y = (short)(y_pxl * 4 / 5);
	end_x = start_x + 10 * (x_pxl / 64 + (x_pxl % 64 != 0)) + 10;
	end_y = start_y + 10 * (y_pxl / 64 + (y_pxl % 64 != 0)) + 10;
	if (x >= start_x && x < end_x && y >= start_y && y < end_y)
		return (1);
	return (0);
}
