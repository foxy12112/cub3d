/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:04:24 by psostari          #+#    #+#             */
/*   Updated: 2025/04/15 12:16:48 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_cub_data *cub, int x, int y, int color)
{
	uint8_t	*pixel;

	if (y < 0 || y >= cub->mlx->height
		|| x < 0 || x >= cub->mlx->width)
		return ;
	pixel = (uint8_t *)(cub->img->pixels
			+ (y * cub->img->width * 4 + x * 4));
	*(int *)pixel = color;
}

void	calculate_column(t_cub_data *cub, int *line_height, \
int *start, int *end)
{
	*line_height = (int)(cub->mlx->height / cub->ray_dir_y);
	*start = -*line_height / 2 + cub->mlx->height / 2;
	if (*start < 0)
		*start = 0;
	*end = *line_height / 2 + cub->mlx->height / 2;
	if (*end >= cub->mlx->height)
		*end = cub->mlx->height - 1;
}

void	calculate_texture(t_cub_data *cub)
{
	double	wall_x;
	int		texture_width;

	if (cub->side == 0)
		wall_x = cub->p->y + cub->ray_dir_y * cub->ray_dir_x;
	else
		wall_x = cub->p->x + cub->ray_dir_x * cub->ray_dir_y;
	wall_x -= floor(wall_x);
	texture_width = (int)(wall_x * 128);
	if (cub->side == 0 && cub->ray_dir_x > 0)
		texture_width = 128 - texture_width - 1;
	if (cub->side == 1 && cub->ray_dir_y < 0)
		texture_width = 128 - texture_width - 1;
}

void	draw_texture(t_cub_data *cub, int x, int texture)
{
	int	color;
	int	y;

	y = 0;
	while (y < cub->mlx->height)
	{
		color = *(int *)(cub->texture->no_tex->pixels
				+ (texture * 4
					+ y * cub->texture->no_tex->width * 4));
		img_pix_put(cub, x, y, color);
		y++;
	}
}

void	draw_column(t_cub_data *cub, int x)
{
	int	line_height;
	int	start;
	int	end;

	calculate_column(cub, &line_height, &start, &end);
	calculate_texture(cub);
	while (start < end)
	{
		if (cub->side == 1 && cub->ray_dir_y < 0)
			draw_texture(cub, x, SOUTH);
		else if (cub->side == 1 && cub->ray_dir_y > 0)
			draw_texture(cub, x, NORTH);
		else if (cub->side == 0 && cub->ray_dir_x < 0)
			draw_texture(cub, x, WEST);
		else if (cub->side == 0 && cub->ray_dir_x > 0)
			draw_texture(cub, x, EAST);
		start++;
	}
}
