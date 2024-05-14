/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:23:17 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/14 15:19:30 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_position
{
	int		x;
	int		y;
	int		orientation;
}	t_position;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	short	*celing;
	short	*floor;
}	t_texture;

typedef struct s_window
{
	void	*mlx;
	void	*win;
}	t_window;

typedef struct s_data
{
	char				**map;
	struct s_texture	*texture;
	struct s_position	*position;
	struct s_window		*window;
}	t_data;

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

short		ft_perror(char *str);
short		check_map(char *map_name, t_data **data);
int			ft_freedata(t_data *data);
t_position	*set_position(int i, int j, char orientation);
int			set_texture(char *map_line, t_texture **texture);

#endif
