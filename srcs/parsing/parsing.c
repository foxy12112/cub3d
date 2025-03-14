/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:55:37 by ldick             #+#    #+#             */
/*   Updated: 2025/02/12 17:54:04 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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