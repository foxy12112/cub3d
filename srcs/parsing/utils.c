/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:04:57 by psostari          #+#    #+#             */
/*   Updated: 2025/03/19 12:20:45 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_leaks(char **map, t_cub_data *cub)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (y == 0 || !map[y - 1] || (y + 1) == (size_t)cub->map_height \
					|| !map[y + 1] || x == 0 || !map[y][x - 1] \
					|| x + 1 == (size_t)ft_strlen(map[y]) || !map[y][x + 1])
					return (ft_error(cub, "overhang not closed"), 1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}

int	check_map_dim(t_cub_data *cub)
{
	if (cub->map_height < 3 || cub->map_width < 3)
	{
		ft_error(cub, "Map is too small, must be at least 3x3");
		return (1);
	}
	return (0);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}
