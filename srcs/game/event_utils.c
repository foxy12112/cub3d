/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:16:36 by ldick             #+#    #+#             */
/*   Updated: 2025/06/03 11:01:33 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_location(t_cub_data *cub, double x, double y)
{
	int	map_x;
	int	map_y;
	int	current_map_x;
	int	current_map_y;

	map_x = (int)x;
	map_y = (int)y;
	current_map_x = 0;
	current_map_y = 0;
	if (cub->map[map_y][map_x] == '1' || cub->map[map_y][map_x] == ' ')
		return (0);
	current_map_x = (int)cub->player_x;
	current_map_y = (int)cub->player_y;
	if (current_map_x != map_x && current_map_y != map_y)
	{
		if (cub->map[current_map_y][map_x] == '1' || cub->map[current_map_y][map_x] == ' ')
			return (0);
		if (cub->map[map_y][current_map_x] == '1' || cub->map[map_y][current_map_x] == ' ')
			return (0);
	}
	return (1);
}
