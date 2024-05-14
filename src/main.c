/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:18:13 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/14 15:11:24 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (perror("Error\nWrong number of arguments"), 1);
	data = malloc(sizeof(t_data));
	if (check_map(argv[1], &data))
		return (ft_freedata(data));
	data->window = malloc(sizeof(t_window));
	data->window->mlx = mlx_init();
	if (!data->window->mlx)
		return (perror("Error\nmlx_init failed"), ft_freedata(data));
	data->window->win = mlx_new_window(data->window->mlx, 1600, 900, "cub3d");
	if (!data->window->win)
		return (perror("Error\nmlx_new_window failed"), ft_freedata(data));
	mlx_loop(data->window->mlx);
	return (0);
}
