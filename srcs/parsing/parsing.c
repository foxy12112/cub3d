/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:55:37 by ldick             #+#    #+#             */
/*   Updated: 2025/04/30 09:09:02 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(t_cub_data *cub)
{
	if (check_map(cub) != 0)
		return (ft_error(cub, "Error in map parsing"), 1);
	if (check_textures(cub) != 0)
		return (ft_error(cub, "Error in texture parsing"), 1);
	if (check_invalid_chars(cub) != 0)
		return (ft_error(cub, "Invalid character in map"), 1);
	if (check_map_dim(cub) != 0)
		return (ft_error(cub, "Map is too small, must be at least 3x3"), 1);
	return (SUCCESS);
}

int	check_invalid_chars(t_cub_data *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] != '1' && cub->map[y][x] != '0' &&
				cub->map[y][x] != 'N' && cub->map[y][x] != 'S' &&
				cub->map[y][x] != 'E' && cub->map[y][x] != 'W' &&
				cub->map[y][x] != ' ' && cub->map[y][x] != '\t')
			{
				return (ft_error(cub, "Invalid character in map"), FAILURE);
			}
			x++;
		}
		y++;
	}
	return (0);
}
// void	minimap_size(t_cub_data *cub)
// {
// 	int	y;

// 	y = 0;
// 	cub->minimap->size_x = 0;
// 	while (cub->map[y])
// 	{
// 		if (y > 0 && cub->map[y + 1] != NULL)
// 			if ((int)ft_strlen(cub->map[y]) >= cub->minimap->size_x)
// 				cub->minimap->size_x = ft_strlen(cub->map[y]);
// 		y++;
// 	}
// 	cub->minimap->size_y = y;
// }

int	parsing(t_cub_data *cub)
{
	if (check_textures(cub) == 1)
		ft_error(cub, "error in textures");
	if (check_map(cub) == 1)
		ft_error(cub, "error in map parsing");
	// minimap_size(cub);
	return (0);
}
