/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:04:24 by psostari          #+#    #+#             */
/*   Updated: 2025/04/30 12:56:16 by ldick            ###   ########.fr       */
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

// void	calculate_column(t_cub_data *cub, int *line_height, \
// int *start, int *end)
// {
// 	*line_height = (int)(cub->mlx->height / cub->perpwalldist);
// 	*start = -*line_height / 2 + cub->mlx->height / 2;
// 	if (*start < 0)
// 		*start = 0;
// 	*end = *line_height / 2 + cub->mlx->height / 2;
// 	if (*end >= cub->mlx->height)
// 		*end = cub->mlx->height - 1;
// }

// void	calculate_texture(t_cub_data *cub)
// {
// 	double	wall_x;
// 	int		texture_width;

// 	if (cub->side == 0)
// 		wall_x = cub->p->y + cub->ray_dir_y * cub->ray_dir_x;
// 	else
// 		wall_x = cub->p->x + cub->perpwalldist * cub->ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	texture_width = (int)(wall_x * 128);
// 	if (cub->side == 0 && cub->ray_dir_x > 0)
// 		texture_width = 128 - texture_width - 1;
// 	if (cub->side == 1 && cub->ray_dir_y < 0)
// 		texture_width = 128 - texture_width - 1;
// }

// void	draw_texture(t_cub_data *cub, int x, int texture)
// {
// 	int	color;
// 	int	y;

// 	y = 0;
// 	while (y < cub->mlx->height)
// 	{
// 		color = *(int *)(cub->texture->no_tex->pixels
// 				+ (texture * 4
// 					+ y * cub->texture->no_tex->width * 4));
// 		img_pix_put(cub, x, y, color);
// 		y++;
// 	}
// }

// void	draw_column(t_cub_data *cub, int x)
// {
// 	int	line_height;
// 	int	start;
// 	int	end;

// 	calculate_column(cub, &line_height, &start, &end);
// 	calculate_texture(cub);
// 	while (start < end)
// 	{
// 		if (cub->side == 1 && cub->ray_dir_y < 0)
// 			draw_texture(cub, x, SOUTH);
// 		else if (cub->side == 1 && cub->ray_dir_y > 0)
// 			draw_texture(cub, x, NORTH);
// 		else if (cub->side == 0 && cub->ray_dir_x < 0)
// 			draw_texture(cub, x, WEST);
// 		else if (cub->side == 0 && cub->ray_dir_x > 0)
// 			draw_texture(cub, x, EAST);
// 		start++;
// 	}
// }

// void	draw_column(t_cub_data *cub, int screen_x)
// {
// 	int		y;
// 	double	step;
// 	double	tex_pos;
// 	int		color;

// 	cub->y = (int)(cub->mlx->height / cub->perpwalldist);
// 	cub->x = -cub->y / 2 + cub->mlx->height / 2;
// 	if (cub->x < 0)
// 	{
// 		cub->x = 0;
// 	}
// 	cub->map_x = cub->y / 2 + cub->mlx->height / 2;
// 	if (cub->map_x >= cub->mlx->height)
// 	{
// 		cub->map_x = cub->mlx->height - 1;
// 	}
// 	calculate_texture(cub);
// 	step = 1.0 * cub->texture->no_tex->height / cub->y;
// 	tex_pos = (cub->x - cub->mlx->height / 2 + cub->y / 2) * step;
// 	y = cub->x;
// 	while (y < cub->map_x)
// 	{
// 		cub->map_y = (int)tex_pos & (cub->texture->no_tex->height - 1);
// 		tex_pos += step;
// 		color = *(int *)(cub->texture->no_tex->pixels
// 				+ 4 * (cub->map_y * cub->texture->no_tex->width + cub->x));
// 		img_pix_put(cub, screen_x, y, color);
// 		y++;
// 	}
// }

mlx_texture_t	*get_wall_texture(t_cub_data *cub)
{
	if (cub->side == 0 && cub->ray_dir_x < 0)
		return (cub->texture->we_tex);
	if (cub->side == 0 && cub->ray_dir_x > 0)
		return (cub->texture->ea_tex);
	if (cub->side == 1 && cub->ray_dir_y < 0)
		return (cub->texture->no_tex);
	return (cub->texture->so_tex);
}

void	calculate_column(t_cub_data *cub, int *line_height, int *start, int *end)
{
	*line_height = (int)(cub->mlx->height / cub->perpwalldist);
	*start = -*line_height / 2 + cub->mlx->height / 2;
	if (*start < 0)
		*start = 0;
	*end = *line_height / 2 + cub->mlx->height / 2;
	if (*end >= cub->mlx->height)
		*end = cub->mlx->height - 1;
}

int	calculate_texture(t_cub_data *cub, mlx_image_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (cub->side == 0)
		wall_x = cub->p->y + cub->perpwalldist * cub->ray_dir_y;
	else
		wall_x = cub->p->x + cub->perpwalldist * cub->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (cub->side == 0 && cub->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (cub->side == 1 && cub->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
void	draw_column(t_cub_data *cub, int x)
{
	int				line_h;
	int				start;
	int				end;
	mlx_image_t		*tex;
	int				y;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	int				color;

	calculate_column(cub, &line_h, &start, &end);
	tex = get_wall_texture(cub);
	tex_x = calculate_texture(cub, tex);
	step = 1.0 * tex->height / line_h;
	tex_pos = (start - cub->mlx->height / 2 + line_h / 2) * step;
	y = start;
	while (y < end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = *(int *)(tex->pixels + 4 * (tex_y * tex->width + tex_x));
		img_pix_put(cub, x, y, color);
		y++;
	}
}
