/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:04:24 by psostari          #+#    #+#             */
/*   Updated: 2025/04/15 10:17:01 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_cub_data *cub, int x, int y, int color)
{
    char    *pixel;

    if (y < 0 || y > cub->height - 1 || x < 0 || x > cub->width - 1)
        return ;
    pixel = (cub->img->pixels + (y * cub->img->width * 4 + x * 4));
    *(int *)pixel = color;
}

void	calculate_column(t_cub_data *cub, int *line_height, int *start, int *end)
{
    *line_height = cub->height / cub->ray_dir_y;
    *start = -*line_height / 2 + cub->height / 2;
    if (*start < 0)
        *start = 0;
    *end = *line_height / 2 + cub->height / 2;
    if (*end >= cub->height)
        *end = cub->height - 1;
}

void	calculate_texture(t_cub_data *cub, int start, int line_height)
{
    if (cub->side == 0)
        cub->wallX = cub->p->y + cub->ray_dir_y * cub->ray_dir_x;
    else
        cub->wallX = cub->p->x + cub->ray_dir_x * cub->ray_dir_y;
    cub->wallX -= floor(cub->wallX);
    cub->texture->we_tex->width = cub->wallX * 128;
    if (cub->side == 0 && cub->ray_dir_x > 0)
        cub->texture->we_tex->width = 128 - cub->texture->we_tex->width - 1;
    if (cub->side == 1 && cub->ray_dir_y < 0)
        cub->texture->we_tex->width = 128 - cub->texture->we_tex->width - 1;
    cub->texture->we_tex->height = 1.0 * 128 / line_height;
    cub->texture->no_tex->height = (start - cub->height / 2 + line_height / 2) * cub->texture->we_tex->height;
}

void	draw_texture(t_cub_data *cub, int x, int texture)
{
    int	color;

    color = *(int *)(cub->texture->no_tex->pixels + (cub->texture->we_tex->width * 4 + cub->texture->no_tex->height * 4));
    img_pix_put(cub, x, cub->texture->no_tex->height, color);
}

void	draw_column(t_cub_data *cub, int x)
{
    int	line_height;

    calculate_column(cub, &line_height, &cub->texture->no_tex->height, &cub->texture->we_tex->height);
    calculate_texture(cub, cub->texture->no_tex->height, line_height);
    while (cub->texture->no_tex->height < cub->texture->we_tex->height)
    {
        cub->texture->we_tex->height = (int)cub->texture->no_tex->height & (128 - 1);
        cub->texture->no_tex->height += cub->texture->we_tex->height;
        if (cub->side == 1 && cub->ray_dir_y < 0)
            draw_texture(cub, x, SOUTH);
        else if (cub->side == 1 && cub->ray_dir_y > 0)
            draw_texture(cub, x, NORTH);
        else if (cub->side == 0 && cub->ray_dir_x < 0)
            draw_texture(cub, x, WEST);
        else if (cub->side == 0 && cub->ray_dir_x > 0)
            draw_texture(cub, x, EAST);
        cub->texture->no_tex->height++;
    }
}
