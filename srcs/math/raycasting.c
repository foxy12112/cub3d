/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:25:41 by psostari          #+#    #+#             */
/*   Updated: 2025/05/18 14:04:07 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_step(t_cub_data *cub)
{
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = ((cub->p->x - 50) / 22 - cub->map_x) * cub->delta_dist_x;
		printf("\n\n\n\n\n\n\n\n\n%f\n\n\n\n\n\n\n", cub->side_dist_x);
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - (cub->p->x - 50) / 22) * cub->delta_dist_x;
	}
	if (cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = ((cub->p->y - 50) / 22 - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - (cub->p->y - 50) / 22) * cub->delta_dist_y;
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
		if (cub->map[cub->map_y][cub->map_x] != '0')
			wall = 1;
	}
}

void	init_ray(t_cub_data *cub, int x)
{
	cub->map_x = (int)(cub->p->x - 50) / 22;
	cub->map_y = (int)(cub->p->y - 50) / 22;
	cub->p->camera_angle = 2 * x / (double)cub->mlx->width - 1;
	cub->ray_dir_x = cub->p->dir_x + cub->p->plane_x * cub->p->camera_angle;
	cub->ray_dir_y = cub->p->dir_y + cub->p->plane_y * cub->p->camera_angle;
	// if (cub->ray_dir_x == 0)
	// 	cub->delta_dist_x = 1e30;
	// else
	// 	cub->delta_dist_x = fabs(1 / cub->ray_dir_x);
	// if (cub->ray_dir_y == 0)
	// 	cub->delta_dist_y = 1e30;
	// else
	// 	cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
	cub->delta_dist_x = sqrt(1 + (cub->ray_dir_y * cub->ray_dir_y) / (cub->ray_dir_x * cub->ray_dir_x));
	cub->delta_dist_y = sqrt(1 + (cub->ray_dir_x * cub->ray_dir_x) / (cub->ray_dir_y * cub->ray_dir_y));
}

void	raycasting(t_cub_data *cub)
{
	int	x;

	x = 0;
	while (x < cub->mlx->width)
	{
		init_ray(cub, x);
		calculate_step(cub);
		perform_dda(cub);
		if (cub->side == 0)
			cub->perpwalldist = ((cub->side_dist_x - cub->delta_dist_x));
		else
			cub->perpwalldist = ((cub->side_dist_y - cub->delta_dist_y));
		printf("%f\t%f\t%f\t%f\t%f\n", cub->perpwalldist, cub->side_dist_x, cub->delta_dist_x, cub->delta_dist_y, cub->side_dist_y);
		draw_column(cub, x);
		x++;
	}
}
