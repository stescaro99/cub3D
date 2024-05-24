/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:35:00 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/21 09:41:20 by stescaro         ###   ########.fr       */
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
