/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:37:21 by ldick             #+#    #+#             */
/*   Updated: 2025/05/29 16:42:14 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_raycasting ray, t_cub_data *cub, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	mlx_texture_t	*texture;
	t_drawing	draw;

	line_height = (int)(HEIGHT / ray.perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	texture = select_texture(cub, ray);
	draw.tex_x = calculate_texture(cub, ray, texture);
	draw.step = (double)texture->height / (double)line_height;
	draw.tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * draw.step;
	while(draw_start <= draw_end)
	{
		draw.tex_y = (int)draw.tex_pos & (texture->height - 1);
		color = get_pixel_color(&(texture->pixels[(draw.tex_y * texture->width + draw.tex_x) * 4]));
		mlx_put_pixel(cub->img, x, draw_start, color);
		draw.tex_pos += draw.step;
		draw_start++;
	}
}

void	draw_background(t_cub_data *cub)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while(y < HEIGHT)
	{
		while(x < WIDHT)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(cub->img, x, y, cub->ceiling);
			else
				mlx_put_pixel(cub->img, x, y, cub->floor);
				x++;
		}
		x = 0;
		y++;
	}
}