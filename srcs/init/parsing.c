/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:07:25 by ldick             #+#    #+#             */
/*   Updated: 2025/06/01 14:59:07 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_cub_data *cub)
{
	if (cub->texture_east)
		free(cub->texture_east);
	if (cub->texture_west)
		free(cub->texture_west);
	if (cub->texture_south)
		free(cub->texture_south);
	if (cub->texture_north)
		free(cub->texture_north);
}

int	parsing(t_cub_data *cub)
{
	if (!add_textures(cub))
		return (free_texture(cub), 0);
	if (!add_map(cub))
		return (0);
	if (!add_player(cub))
		return (free_texture(cub), free_split(cub->map), 0);
	correct_map(cub);
	return (1);
}
