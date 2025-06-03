/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:07:25 by ldick             #+#    #+#             */
/*   Updated: 2025/06/03 14:44:15 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_cub_data *cub)
{
	if (cub->counter.east_texture != 0 && cub->texture_east)
		mlx_delete_texture(cub->texture_east);
	if (cub->counter.west_texture != 0 && cub->texture_south)
		mlx_delete_texture(cub->texture_west);
	if (cub->counter.south_texture != 0 && cub->texture_west)
		mlx_delete_texture(cub->texture_south);
	if (cub->counter.north_texture != 0 && cub->texture_north)
		mlx_delete_texture(cub->texture_north);
}

int	parsing(t_cub_data *cub)
{
	if (!add_textures(cub))
		return (0);
	if (!add_map(cub))
		return (0);
	if (!add_player(cub))
		return (printf("Error\ntoo many players, or none\n"), 0);
	correct_map(cub);
	return (1);
}
