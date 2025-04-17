/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:16:09 by psostari          #+#    #+#             */
/*   Updated: 2025/04/17 08:55:33 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check collision at a specific position
bool	check_collision(t_cub_data *cub, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (cub->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

// Check collision above the player
bool	collision_top(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x;
	y = cub->p->y - 0.05;
	while (x <= cub->p->x + 0.56)
	{
		if (cub->map[(int)y][(int)x] == '1')
			return (true);
		x += 0.05;
	}
	return (false);
}

// Check collision below the player
bool	collision_bottom(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x;
	y = cub->p->y - 0.05;
	while (x <= cub->p->x + 0.56)
	{
		if (cub->map[(int)(y + 0.65)][(int)x] == '1')
			return (true);
		x += 0.05;
	}
	return (false);
}

// Check collision to the left of the player
bool	collision_left(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x - 0.05;
	y = cub->p->y;
	while (y <= cub->p->y + 0.55)
	{
		if (cub->map[(int)y][(int)x] == '1')
			return (true);
		y += 0.05;
	}
	return (false);
}

// Check collision to the right of the player
bool	collision_right(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x - 0.05;
	y = cub->p->y;
	while (y <= cub->p->y + 0.56)
	{
		if (cub->map[(int)y][(int)(x + 0.65)] == '1')
			return (true);
		y += 0.05;
	}
	return (false);
}
