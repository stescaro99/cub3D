/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:15:06 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/24 15:50:41 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_closegame(t_data *data)
{
	ft_freedata(data);
	exit(0);
	return (1);
}

void	ft_rotate(t_position **pos, int x_or, int grad)
{
	if (x_or)
		(*pos)->angle -= grad;
	else
		(*pos)->angle += grad;
	if ((*pos)->angle < 0)
		(*pos)->angle += 360;
	else if ((*pos)->angle >= 360)
		(*pos)->angle -= 360;
	printf("angle: %d\n", (*pos)->angle);
}

static	int	ft_keyhook(int keysym, t_data **data)
{
	(void)data;
	if (keysym == 65307)
		ft_closegame(*data);
	if (keysym == XK_w || keysym == XK_s || keysym == XK_a || keysym == XK_d)
	{
		ft_move(&(*data)->map, &(*data)->position, keysym);
		//reycast;
		display_minimap(*data, (*data)->imgs);
	}
	else if (keysym == XK_Left || keysym == XK_Right)
	{
		ft_rotate(&(*data)->position, (keysym == XK_Right), 4);
		//reycast;
	}
	return (0);
}

static	int	ft_mousehook(int x, int y, t_data **data)
{
	int			x_or;
	static int	past_x = 800;
	static int	pixel = 0;
	int			pixel_x;
	int			rot;

	(void)y;
	pixel_x = x - past_x;
	printf("pixel_x: %d\n", pixel_x);
	printf("pixel: %d\n", pixel);
	if (pixel_x % 2 && pixel_x > 0)
		pixel++;
	else if (pixel_x % 2 && pixel_x < 0)
		pixel--;
	rot = pixel_x / 2 + pixel / 2;
	if (pixel % 2 == 0)
		pixel = 0;
	x_or = (x > past_x);
	if (x != past_x && rot)
		ft_rotate(&(*data)->position, x_or, rot);
	//reycast
	past_x = x;
	return (0);
}

void	cub3d(t_data *data)
{
	display_minimap(data, data->imgs);
	mlx_hook(data->window->win, 2, 1L << 0, ft_keyhook, &data);
	mlx_hook(data->window->win, 6, 1L << 6, ft_mousehook, &data);
	mlx_hook(data->window->win, 17, 1L << 17, ft_closegame, data);
	mlx_loop(data->window->mlx);
}
