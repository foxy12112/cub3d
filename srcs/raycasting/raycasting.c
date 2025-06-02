/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:02:49 by ldick             #+#    #+#             */
/*   Updated: 2025/06/02 16:05:23 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_raycasting	perform_dda(t_raycasting ray, t_cub_data *cub)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray.sidedist_x < ray.sidedist_y)
		{
			ray.sidedist_x += ray.deltadist_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.sidedist_y += ray.deltadist_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (cub->map[ray.map_y][ray.map_x] != '0')
			break ;
	}
	if (ray.side == 0)
		ray.perp_wall_dist = (ray.sidedist_x - ray.deltadist_x);
	else
		ray.perp_wall_dist = (ray.sidedist_y - ray.deltadist_y);
	return (ray);
}

mlx_texture_t	*select_texture(t_cub_data *cub, t_raycasting ray)
{
	if (ray.side == 0 && ray.ray_dir_x < 0)
		return (cub->texture_west);
	if (ray.side == 0 && ray.ray_dir_x > 0)
		return (cub->texture_east);
	if (ray.side == 1 && ray.ray_dir_y < 0)
		return (cub->texture_north);
	return (cub->texture_south);
}

int	calculate_texture(t_cub_data *cub, t_raycasting ray, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray.side == 0)
		wall_x = cub->player_y + ray.perp_wall_dist * ray.ray_dir_y;
	else
		wall_x = cub->player_x + ray.perp_wall_dist * ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	if (ray.side == 0 && ray.ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray.side == 1 && ray.ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	dda_loop(t_cub_data *cub)
{
	t_raycasting	ray;
	t_direction		dir;
	int				x;
	double			old_dir_x;

	x = -1;
	dir.temp_dir_x = cub->player_direction_x;
	dir.temp_dir_y = cub->player_direction_y;
	dir.dir_inc = FOV * (M_PI / 180) / (double)WIDHT;
	old_dir_x = dir.temp_dir_x;
	dir.temp_dir_x = dir.temp_dir_x * cos(-((FOV * (M_PI / 180)) / 2))
		- dir.temp_dir_y * sin(-((FOV * (M_PI / 180)) / 2));
	dir.temp_dir_y = old_dir_x * sin(-((FOV * (M_PI / 180)) / 2))
		+ dir.temp_dir_y * cos(-((FOV * (M_PI / 180)) / 2));
	while (++x < WIDHT)
	{
		init_dda(cub, &ray, x, dir);
		ray = perform_dda(ray, cub);
		draw_line(ray, cub, x);
		old_dir_x = dir.temp_dir_x;
		dir.temp_dir_x = dir.temp_dir_x * cos(dir.dir_inc) - dir.temp_dir_y
			* sin(dir.dir_inc);
		dir.temp_dir_y = old_dir_x * sin(dir.dir_inc) + dir.temp_dir_y
			* cos(dir.dir_inc);
	}
}

// TODO fix plane, completelly wrong wa da faq