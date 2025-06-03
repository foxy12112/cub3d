/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:41:17 by ldick             #+#    #+#             */
/*   Updated: 2025/06/03 11:03:14 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_step(t_cub_data *cub, t_raycasting *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (cub->player_x - (double)ray->map_x)
			* ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = ((double)ray->map_x + 1.0 - cub->player_x)
			* ray->deltadist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (cub->player_y - (double)ray->map_y)
			* ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = ((double)ray->map_y + 1.0 - cub->player_y)
			* ray->deltadist_y;
	}
}

void	init_dda(t_cub_data *cub, t_raycasting *ray, int x)
{
	ray->map_x = (int)(cub->player_x);
	ray->map_y = (int)(cub->player_y);
	ray->camera_x = (double)2 * (double)x / (double)WIDHT - 1.0;
	ray->ray_dir_x = cub->player_direction_x + cub->player_plane_x
		* ray->camera_x;
	ray->ray_dir_y = cub->player_direction_y + cub->player_plane_y
		* ray->camera_x;
	if (ray->ray_dir_x == 0)
		ray->deltadist_x = 1e30;
	else
		ray->deltadist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->deltadist_y = 1e30;
	else
		ray->deltadist_y = fabs(1 / ray->ray_dir_y);
	choose_step(cub, ray);
}
