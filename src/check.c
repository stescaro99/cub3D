/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:42:29 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/14 14:50:36 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	short	sb_wall(char **map, int i, int j)
{
	if (i == 0 || !map[i + 1] || j == 0 || j == (int)ft_strlen(map[i]) - 1)
		return (1);
	if ((int)ft_strlen(map[i - 1]) <= j || (int)ft_strlen(map[i + 1]) <= j)
		return (1);
	if (j > 0 && map[i][j - 1] == ' ')
		return (1);
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		return (1);
	return (0);
}

static	short	check_spaces(char **map, int i, int j)
{
	if (i > 0 && map[i - 1][j] != ' ' && map[i - 1][j] != '1')
		return (1);
	if (map[i + 1] && map[i + 1][j] != ' ' && map[i + 1][j] != '1')
		return (1);
	if (j > 0 && map[i][j - 1] != ' ' && map[i][j - 1] != '1')
		return (1);
	if (map[i][j + 1] && map[i][j + 1] != ' ' && map[i][j + 1] != '1')
		return (1);
	return (0);
}

static	short	check_map_content(char **map, t_data **data)
{
	int		i;
	int		j;

	i = -1;
	(*data)->position = NULL;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ' && check_spaces(map, i, j))
				return (perror("Error\nSpaces not surrounded by walls"), 1);
			else if (map[i][j] != ' ' && sb_wall(map, i, j) && map[i][j] != '1')
				return (perror("Error\nMap is not surrounded by walls"), 1);
			else if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W') && !(*data)->position)
				(*data)->position = set_position(i, j, map[i][j]);
			else if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				return (perror("Error\nMultiple starting positions"), 1);
			else if (map[i][j] & ~('1' | '0' | ' ' | 'D'))
				return (perror("Error\nInvalid character in the map"), 1);
		}
	}
	return (!(*data)->position && ft_perror("Error\nNo starting position"));
}

short	check_map(char *map_name, t_data **data)
{
	int			fd;
	char		*map_line;
	t_data		*tmp;
	int			start;

	tmp = *data;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nCan't open the map file"), 1);
	map_line = malloc(50000);
	if (read(fd, map_line, 50000) < 0)
		return (perror("Error\nCan't read the map file"), 1);
	(*data)->texture = ft_calloc(sizeof(t_texture), 1);
	start = set_texture(map_line, &((*data)->texture));
	if (start < 0 || !(*data)->texture->no || !(*data)->texture->so
		|| !(*data)->texture->we || !(*data)->texture->ea
		|| !(*data)->texture->celing || !(*data)->texture->floor)
		return ((start < 0 || ft_perror("Error\nTexture path missing")));
	tmp->map = ft_split(&map_line[start], '\n');
	free(map_line);
	if (!tmp->map)
		return (perror("Error\nMap allocation failed"), 1);
	close(fd);
	return (check_map_content(tmp->map, data));
}
