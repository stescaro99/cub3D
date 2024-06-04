/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:35:00 by stescaro          #+#    #+#             */
/*   Updated: 2024/06/04 14:51:23 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

short	ft_perror(char *str)
{
	perror(str);
	return (1);
}

int	count_nl(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == '\n')
		i++;
	return (i);
}

t_position	*set_position(int i, int j, char orientation)
{
	t_position	*position;

	position = ft_calloc(sizeof(t_position), 1);
	if (!position)
		return (NULL);
	position->x = j + 0.5;
	position->y = i + 0.5;
	position->angle = 0 + M_PI * 0.5 * (orientation == 'N')
		+ M_PI * (orientation == 'W') + M_PI * 1.5 * (orientation == 'S');
	position->tile = '0';
	return (position);
}

void	*find_img_ptr(t_imgs *img, char c)
{
	if (c == 0)
		return (img->empty);
	else if (c == '1' || c == 'i' || c == 'I')
		return (img->wall);
	else if (c == '0')
		return (img->floor);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (img->player);
	else if (c == 'D' || c == 'd')
		return (img->door);
	else if (c == 'w')
		return (img->w_wall);
	else if (c == 'e')
		return (img->e_wall);
	else if (c == 'n')
		return (img->n_wall);
	else if (c == 's')
		return (img->s_wall);
	else if (c == 'I')
		return (img->door_closed);
	return (img->door_open);
}

