/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:23:17 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/24 14:24:36 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>

typedef struct s_position
{
	int		x;
	int		y;
	int		angle;
	int		int_x;
	int		int_y;
	double	time;
	double	old_time;
	char	tile;
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

typedef struct s_map
{
	short	lenght;
	short	height;
	char	**map;
}	t_map;

typedef struct s_imgs
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*door;
	void	*empty;
	void	*n_wall;
	void	*s_wall;
	void	*w_wall;
	void	*e_wall;
}	t_imgs;

typedef struct s_data
{
	struct s_map		*map;
	struct s_texture	*texture;
	struct s_position	*position;
	struct s_window		*window;
	struct s_imgs		*imgs;
}	t_data;

void		cub3d(t_data *data);
short		ft_perror(char *str);
short		check_map(char *mn, t_texture **tt, t_map **map, t_data **data);
int			ft_freedata(t_data *data);
t_position	*set_position(int i, int j, char orientation);
int			set_texture(char *map_line, t_texture **texture);
void		display_minimap(t_data *data, t_imgs *img);
int			ft_closegame(t_data *data);
int			count_nl(char *s);
void		free_imgs(t_imgs *imgs, void *mlx);
void		ft_move(t_map **map, t_position **pos, int key);

#endif