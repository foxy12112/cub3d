/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:25:41 by psostari          #+#    #+#             */
/*   Updated: 2025/05/20 12:24:21 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_step(t_cub_data *cub)
{
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = ((cub->p->x - 50)  - cub->map_x * 22) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = ((cub->map_x + 1.0) * 22 - (cub->p->x - 50)) * cub->delta_dist_x;
	}
	if (cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = ((cub->p->y - 50) - cub->map_y * 22) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = ((cub->map_y + 1.0) * 22 - (cub->p->y - 50)) * cub->delta_dist_y;
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
	cub->delta_dist_x = fabs(1 / cub->ray_dir_x);
	cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
	// cub->delta_dist_x = sqrt(1 + (cub->ray_dir_y * cub->ray_dir_y) / (cub->ray_dir_x * cub->ray_dir_x));
	// cub->delta_dist_y = sqrt(1 + (cub->ray_dir_x * cub->ray_dir_x) / (cub->ray_dir_y * cub->ray_dir_y));
}

// void	raycasting(t_cub_data *cub)
// {
// 	int	x;

// 	x = 0;
// 	while (x < cub->mlx->width)
// 	{
// 		init_ray(cub, x);
// 		calculate_step(cub);
// 		perform_dda(cub);
// 		if (cub->side == 0)
// 			cub->perpwalldist = ((cub->side_dist_x - cub->delta_dist_x));
// 		else
// 			cub->perpwalldist = ((cub->side_dist_y - cub->delta_dist_y));
// 		printf("%f\t%f\t%f\t%f\t%f\n", cub->perpwalldist, cub->side_dist_x, cub->delta_dist_x, cub->delta_dist_y, cub->side_dist_y);
// 		draw_column(cub, x);
// 		x++;
// 	}
// }


void	raycasting(t_cub_data *cub)
{
	int		x = 0;
	while(x < WIDHT)
	{
		double camerax = 2 * x / (double)WIDHT - 1;
		double raydirx = cub->p->dir_x + cub->p->plane_x * camerax;
		double raydiry = cub->p->dir_y + cub->p->plane_y * camerax;
		
		int mapx = (int)((cub->p->x - 50) / 22);
		int mapy = (int)((cub->p->y - 50) / 22);
		double	sidedistx;
		double	sidedisty;
		double	deltadistx = sqrt(1 + pow(raydiry, 2) / pow(raydirx, 2));
		double	deltadisty = sqrt( 1 + pow(raydirx, 2) / pow(raydiry, 2));
		double	perpwalldist;
		
		int stepx;
		int stepy;
		
		int hit = 0;
		int side;
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (((cub->p->x - 50) / 22) - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - ((cub->p->x - 50) / 22)) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedistx = (((cub->p->y - 50) / 22) - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - ((cub->p->y - 50) / 22)) * deltadisty;
		}
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (cub->map[mapy][mapx] != '0')
				hit = 1;
		}
		if (side == 0)
			perpwalldist = (sidedistx - deltadistx);
		else
			perpwalldist = (sidedisty - deltadisty);
		int line_height = (int) HEIGHT / perpwalldist;
		int drawstart = -line_height / 2 + HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = line_height / 2 + HEIGHT / 2;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;
		double wallx;
		mlx_texture_t *tex;
		if (side == 0 && raydirx < 0)
			tex = cub->texture->we_tex;
		else if (side == 0 && raydirx > 0)
			tex = cub->texture->ea_tex;
		else if (side == 1 && raydiry < 0)
			tex = cub->texture->no_tex;
		else
			tex = cub->texture->so_tex;
		if (side == 0)
			wallx = cub->p->y+ perpwalldist * raydiry;
		else
			wallx = cub->p->x + perpwalldist * raydirx;
		wallx -= floor(wallx);
		int texx = (int)(wallx * (double)(tex->width));
		if (side == 0 && raydirx > 0)
			texx = tex->width - texx - 1;
		if (side == 1 && raydiry < 0)
			texx = tex->width - texx - 1;
		double step = 1.0 * tex->height / line_height;
		double texpos = (drawstart - HEIGHT / 2 + line_height / 2) * step;
		int y = drawstart;
		printf("%d\t\t\td\n", drawstart);
		while (y < drawend)
		{
			int texy = (int)texpos & (tex->height - 1);
			texpos += step;
			uint8_t r = tex->pixels[(tex->height * texy + texx) * 4];
			uint8_t g = tex->pixels[(tex->height * texy + texx) * 4 + 1];
			uint8_t b = tex->pixels[(tex->height * texy + texx) * 4 + 2];
			uint8_t a = tex->pixels[(tex->height * texy + texx) * 4 + 3];
			uint32_t color = get_color(r, g, b, a);
			mlx_put_pixel(cub->img, x, y, color);
			y++;
		}
		x++;
	}
}