/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:07:25 by ldick             #+#    #+#             */
/*   Updated: 2025/06/02 15:14:15 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_cub_data *cub)
{
	if (cub->texture_east)
		mlx_delete_texture(cub->texture_east);
	if (cub->texture_west)
		mlx_delete_texture(cub->texture_west);
	if (cub->texture_south)
		mlx_delete_texture(cub->texture_south);
	if (cub->texture_north)
		mlx_delete_texture(cub->texture_north);
}

int	parsing(t_cub_data *cub)
{
	if (!add_textures(cub))
		return (0);
	if (!add_map(cub))
		return (0);
	if (!add_player(cub))
		return (free_split(cub->map), 0);
	correct_map(cub);
	return (1);
}
