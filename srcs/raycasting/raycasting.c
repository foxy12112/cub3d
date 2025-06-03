/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:02:49 by ldick             #+#    #+#             */
/*   Updated: 2025/06/03 10:33:55 by ldick            ###   ########.fr       */
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
	int				x;
	double			plane_len;
	
	plane_len = tan(FOV * 0.5 * M_PI / 180);
	x = -1;
	while (++x < WIDHT)
	{
		cub->player_plane_x = -cub->player_direction_y * plane_len;
		cub->player_plane_y = cub->player_direction_x * plane_len;
		init_dda(cub, &ray, x);
		ray = perform_dda(ray, cub);
		draw_line(ray, cub, x);
	}
}
// TODO fix plane, completelly wrong wa da faq