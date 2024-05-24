/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:42:29 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/21 10:39:31 by stescaro         ###   ########.fr       */
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

static	short	check_map_content(char **map, t_position **pos)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ' && check_spaces(map, i, j))
				return (perror("Error\nSpaces not surrounded by walls"), 1);
			else if (map[i][j] != ' ' && sb_wall(map, i, j) && map[i][j] != '1'
				&& map[i][j] != 'w')
				return (perror("Error\nMap is not surrounded by walls"), 1);
			else if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W') && !(*pos))
				(*pos) = set_position(i, j, map[i][j]);
			else if (ft_strchr("NSWE", map[i][j]))
				return (perror("Error\nMultiple starting positions"), 1);
			else if (map[i][j] & ~('1' | '0' | ' ' | 'D' | 'w'))
				return (perror("Error\nInvalid character in the map"), 1);
		}
	}
	return (!(*pos) && ft_perror("Error\nNo starting position"));
}

static	t_map	*set_map(char *map_line, int start)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (NULL);
	map->map = ft_split(&map_line[start], '\n');
	if (!map->map)
		return (free(map), NULL);
	free(map_line);
	map->lenght = 0;
	map->height = 0;
	while (map->map[map->height])
	{
		if ((int)ft_strlen(map->map[map->height]) > map->lenght)
			map->lenght = ft_strlen(map->map[map->height]);
		map->height++;
	}
	return (map);
}

short	check_map(char *mn, t_texture **tt, t_map **map, t_data **data)
{
	int			fd;
	char		*map_line;
	int			start;

	fd = open(mn, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nCan't open the map file"), 1);
	map_line = ft_calloc(50000, 1);
	if (read(fd, map_line, 50000) < 0)
		return (perror("Error\nCan't read the map file"), 1);
	close(fd);
	(*tt) = ft_calloc(sizeof(t_texture), 1);
	if (!(*tt))
		return (perror("Error\nTexture allocation failed"), free(map_line), 1);
	start = set_texture(map_line, tt);
	if (start < 0)
		return (free(map_line), 1);
	(*map) = set_map(map_line, start);
	if (!map)
		return (perror("Error\nMap allocation failed"), 1);
	if (start < 0 || !(*tt)->no || !(*tt)->so
		|| !(*tt)->we || !(*tt)->ea
		|| !(*tt)->celing || !(*tt)->floor)
		return ((start < 0 || ft_perror("Error\nTexture path missing")));
	return (check_map_content((*map)->map, &((*data)->position)));
}
