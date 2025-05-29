/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:16:36 by ldick             #+#    #+#             */
/*   Updated: 2025/05/29 16:07:34 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_location(t_cub_data *cub, int move_speed, int x, int y)
{
	(void)move_speed; // TODO remove
	if (!cub->map || !cub->map[y] || !cub->map[y][x])
		return (0);
	if (cub->map[y][x] == '1' || cub->map[y][x] == ' ')
		return (0);
	return (1);
}