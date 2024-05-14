/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:02:50 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/14 14:17:02 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_position	*set_position(int i, int j, char orientation)
{
	t_position	*position;

	position = malloc(sizeof(t_position));
	if (!position)
		return (NULL);
	position->x = j;
	position->y = i;
	if (orientation == 'N')
		position->orientation = 0;
	else if (orientation == 'E')
		position->orientation = 1;
	else if (orientation == 'S')
		position->orientation = 2;
	else
		position->orientation = 3;
	return (position);
}

static	int	set_color(char *s, t_texture **texture)
{
	int		ck;

	ck = 0;
	if (!ft_strncmp(s, "F ", 2) && ++ck && !(*texture)->floor && ck--)
	{
		(*texture)->floor = ft_calloc(sizeof(short), 3);
		(*texture)->floor[0] = ft_atoi(s + 2);
		(*texture)->floor[1] = ft_atoi(ft_strchr(s, ',') + 1);
		(*texture)->floor[2] = ft_atoi(ft_strrchr(s, ',') + 1);
	}
	else if (++ck && !(*texture)->celing && ck--)
	{
		(*texture)->celing = ft_calloc(sizeof(short), 3);
		(*texture)->celing[0] = ft_atoi(s + 2);
		(*texture)->celing[1] = ft_atoi(ft_strchr(s, ',') + 1);
		(*texture)->celing[2] = ft_atoi(ft_strrchr(s, ',') + 1);
	}
	return (ck);
}

static	int	set_textures(char *s, t_texture **texture)
{
	int		ck;

	ck = 0;
	if (s[0] == '1' || s[0] == ' ')
		return (-1);
	else if (!ft_strncmp(s, "NO ", 3) && ++ck && !(*texture)->no && ck--)
		(*texture)->no = ft_strdup(s + 3);
	else if (!ft_strncmp(s, "SO ", 3) && ++ck && !(*texture)->so && ck--)
		(*texture)->so = ft_strdup(s + 3);
	else if (!ft_strncmp(s, "WE ", 3) && ++ck && !(*texture)->we && ck--)
		(*texture)->we = ft_strdup(s + 3);
	else if (!ft_strncmp(s, "EA ", 3) && ++ck && !(*texture)->ea && ck--)
		(*texture)->ea = ft_strdup(s + 3);
	else if (!ft_strncmp(s, "F ", 2) || !ft_strncmp(s, "C ", 2))
		ck = set_color(s, texture);
	else if (s[0] != '\n' && !ck)
		return (perror("Error\nInvalid texture"), 1);
	if (ck > 0)
		return (perror("Error\nDuplicate texture"), 1);
	return (0);
}

static	int	count_nl(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == '\n')
		i++;
	return (i);
}

int	set_texture(char *map_line, t_texture **texture)
{
	char	**split;
	int		i;
	int		res;
	int		ret;

	split = ft_split(map_line, '\n');
	if (!split)
		return (perror("Error\nAllocation failed"), -1);
	i = -1;
	ret = count_nl(map_line);
	while (split[++i])
	{
		res = set_textures(split[i], texture);
		if (res > 0)
			return (ft_freesplit(split), -1);
		if (res < 0)
			break ;
		ret += ft_strlen(split[i]);
		ret += count_nl(&map_line[ret]);
	}
	return (ft_freesplit(split), ret);
}
