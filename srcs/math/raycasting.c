/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:23:31 by psostari          #+#    #+#             */
/*   Updated: 2025/04/15 10:23:13 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_dist(t_cub_data *cub)
{
	if (cub->ray_dir_x == 0)
		cub->delta_dist_x = INT_MAX;
	else
		cub->delta_dist_x = fabs(1 / cub->ray_dir_x);
	if (cub->ray_dir_y == 0)
		cub->delta_dist_y = INT_MAX;
	else
		cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
}

void	calculate_step(t_cub_data *cub)
{
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = (cub->p->x - cub->map_x) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->p->x) * cub->delta_dist_x;
	}
	if (cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = (cub->p->y - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - cub->p->y) * cub->delta_dist_y;
	}
}

void	perform_dda(t_cub_data *cub)
{
	int	wall;

	wall = 0;
	while (wall == 0)
	{
		if (cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			cub->map_x += cub->step_x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			cub->side = 1;
		}
		if (cub->map[cub->map_y][cub->map_x] == '1')
			wall = 1;
	}
}

void	init_ray(t_cub_data *cub, int x)
{
	cub->map_x = (int)cub->p->x;
	cub->map_y = (int)cub->p->y;
	cub->camera_angle = 2 * x / (double)cub->mlx->width - 1;
	cub->ray_dir_x = cub->p->dir_x + cub->p->plane_x * cub->camera_angle;
	cub->ray_dir_y = cub->p->dir_y + cub->p->plane_y * cub->camera_angle;
}

void	raycasting(t_cub_data *cub)
{
	int	x;

	x = 0;
	while (x < cub->mlx->width)
	{
		init_rayc(cub, x);
		calculate_dist(cub);
		calculate_step(cub);
		perform_dda(cub);
		if (cub->side == 0)
			cub->perpwalldist = ((cub->side_dist_x - cub->delta_dist_x));
		else
			cub->perpwalldist = ((cub->side_dist_y - cub->delta_dist_y));
		draw_column(cub, x);
		x++;
	}
}

