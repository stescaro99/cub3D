/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:15:06 by stescaro          #+#    #+#             */
/*   Updated: 2024/06/04 16:03:42 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	ft_keyhook(int keysym, t_data **data)
{
	t_cmds	*cmds;

	if (keysym == 65307)
		ft_closegame(*data);
	cmds = (*data)->cmds;
	if (keysym == XK_w)
		cmds->move_y = 1;
	else if (keysym == XK_s)
		cmds->move_y = -1;
	else if (keysym == XK_a)
		cmds->move_x = -1;
	else if (keysym == XK_d)
		cmds->move_x = 1;
	else if (keysym == XK_Left)
		cmds->rotate = 1;
	else if (keysym == XK_Right)
		cmds->rotate = -1;
	else if (keysym == 65293)
		cmds->open = 1;
	return (0);
}

static	int	ft_keyrelease(int keysym, t_cmds **cmds)
{
	if (keysym == XK_w || keysym == XK_s)
		(*cmds)->move_y = 0;
	else if (keysym == XK_a || keysym == XK_d)
		(*cmds)->move_x = 0;
	else if (keysym == XK_Left || keysym == XK_Right)
		(*cmds)->rotate = 0;
	else if (keysym == 65293)
		(*cmds)->open = 0;
	return (0);
}

static	int	ft_mousehook(int x, int y, t_cmds **cmds)
{
	static int	past_x = 800;
	static int	pixel = 0;
	int			pixel_x;
	int			rot;

	(void)y;
	pixel_x = x - past_x;
	if (pixel_x % 2 && pixel_x > 0)
		pixel++;
	else if (pixel_x % 2 && pixel_x < 0)
		pixel--;
	rot = (pixel_x / 2 + pixel / 2) * M_PI / 180;
	if (pixel % 2 == 0)
		pixel = 0;
	if (x > past_x)
		rot = -rot;
	if (rot)
		(*cmds)->rotate = rot;
	past_x = x;
	return (0);
}

static	int	ft_render(t_data **data)
{
	void	*img;

	handle_cmds((*data)->cmds, &(*data)->map, &(*data)->position);
	img = raycast(*data, (*data)->position->angle - M_PI / 6);
	mlx_put_image_to_window((*data)->window->mlx, (*data)->window->win,
		img, 0, 0);
	mlx_destroy_image((*data)->window->mlx, img);
	return (0);
}

void	cub3d(t_data *data)
{
	mlx_hook(data->window->win, 2, 1L << 0, ft_keyhook, &data);
	mlx_hook(data->window->win, MotionNotify, PointerMotionMask,
		ft_mousehook, &(data->cmds));
	mlx_key_hook(data->window->win, ft_keyrelease, &(data->cmds));
	mlx_hook(data->window->win, 17, 1L << 17, ft_closegame, data);
	mlx_loop_hook(data->window->mlx, ft_render, &data);
	mlx_loop(data->window->mlx);
}
