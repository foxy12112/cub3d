/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:16:36 by ldick             #+#    #+#             */
/*   Updated: 2025/05/30 19:34:44 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_location(t_cub_data *cub, int x, int y)
{
	int	x1;
	int	y1;

	x1 = (cub->player_x * 22 + 5) / 22;
	y1 = (cub->player_y * 22 + 5) / 22;
	if (!cub->map || !cub->map[y] || !cub->map[y][x])
		return (0);
	if (cub->map[y][x] == '1' || cub->map[y][x] == ' ')
		return (0);
	if (cub->map[y1][x1] == '1' || cub->map[y1][x1] == ' ')
		return (0);
	x1 = cub->player_x;
	if (cub->map[y1][x1] == '1' || cub->map[y1][x1] == ' ')
		return (0);
	x1 = (cub->player_x * 22 + 5) / 22;
	y1 = cub->player_y;
	if (cub->map[y1][x1] == '1' || cub->map[y1][x1] == ' ')
		return (0);
	return (1);
}
