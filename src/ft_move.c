/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:53:44 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/24 14:59:06 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	change_map(t_map **m, t_position **p, int prev_x, int prev_y)
{
	char	tile;

	tile = (*m)->map[(*p)->y][(*p)->x];
	if (tile == '1')
	{
		(*p)->x = prev_x;
		(*p)->y = prev_y;
		(*p)->int_x = 1699 * ((*p)->int_x < 100);
		(*p)->int_y = 1699 * ((*p)->int_y < 100);
		return ;
	}
	(*m)->map[(*p)->y][(*p)->x] = 'N';
	(*m)->map[prev_y][prev_x] = (*p)->tile;
	(*p)->tile = tile;
}

static	void	change_cell(t_map **m, t_position **p)
{
	int	x;
	int	y;

	x = (*p)->x;
	y = (*p)->y;
	if ((*p)->int_x < 0)
	{
		(*p)->int_x += 1700;
		(*p)->x--;
	}
	else if ((*p)->int_x >= 1700)
	{
		(*p)->int_x -= 1700;
		(*p)->x++;
	}
	if ((*p)->int_y < 0)
	{
		(*p)->int_y += 1700;
		(*p)->y++;
	}
	else if ((*p)->int_y >= 1700 && (*p)->y--)
		(*p)->int_y -= 1700;
	change_map(m, p, x, y);
}

static	void	move_to_next_minicell(t_map **m, t_position **p, int cs, int sn)
{
	(*p)->int_x += cs;
	(*p)->int_y += sn;
	if ((*p)->int_x < 0 || (*p)->int_y < 0
		|| (*p)->int_x >= 1700 || (*p)->int_y >= 1700)
		change_cell(m, p);
}

void	ft_move(t_map **map, t_position **pos, int key)
{
	double	cs;
	double	sn;
	double	rad;
	int		angle_key;

	if (key == XK_w)
		angle_key = (*pos)->angle;
	else if (key == XK_s)
		angle_key = (*pos)->angle + 180;
	else if (key == XK_a)
		angle_key = (*pos)->angle + 90;
	else
		angle_key = (*pos)->angle - 90;
	if (angle_key < 0)
		angle_key += 360;
	else if (angle_key >= 360)
		angle_key -= 360;
	rad = angle_key * M_PI / 180;
	cs = cos(rad) * 100;
	sn = sin(rad) * 100;
	move_to_next_minicell(map, pos, (int)cs, (int)sn);
}
