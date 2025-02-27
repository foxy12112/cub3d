/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:51:48 by ldick             #+#    #+#             */
/*   Updated: 2025/02/27 12:59:07 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_pixels(uint8_t *dst, uint8_t *src)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = src[3];
}

void	scale(mlx_texture_t *new, mlx_texture_t *tex, int width, int height)
{
	int	x;
	int	y;
	int	src;
	int	dst;
	int	temp;

	y = 0;
	while(y < height)
	{
		x = 0;
		while(x < width)
		{
			temp = x * tex->width / width;
			src = ((y * tex->height / height) * tex->width + temp) * 4;
			dst = (y * width + x) * 4;
			copy_pixels(&new->pixels[dst], &tex->pixels[src]);
			x++;
		}
		y++;
	}
}

void	draw_line(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx;
	int	dy;
	int	dir;
	int	i;
	int	p;
	int y;

	i = 0;
	if (x0 > x1)
	{
		ft_swap(&x0, &x1, sizeof(int));
		ft_swap(&y0, &y1, sizeof(int));
	}
	dx = x1 - x0;
	dy = y1 - y0;
	dir = (dy < 0) ? -1 : 1;
	dy *= dir;
	if (dx != 0)
	{
		y = y0;
		p = 2 * dy - dx;
		while(i < dx + 1)
		{
			mlx_put_pixel(cub->img, x0 + i, y, 0x64);
			if (p >= 0)
			{
				y += dir;
				p = p - 2 * dx;
			}
			p = p + 2 * dy;
			i++;
		}
	}
}

void	draw_ray(t_cub_data *cub)
{
	int x1;
	int	y1;
	int	x;
	int	y;
	double angle;

	angle = cub->p->dir * (M_PI / 180.0);
	x1 = cub->minimap->p_img->instances[0].x + 50;
	y1 = cub->minimap->p_img->instances[0].y + 50;
	printf("%0.5f\n", angle);
	x = x1 + cos(angle) * 200;
	y = y1 + sin(angle) * 200;
	draw_line(x1, y1, x, y, cub);
}

void	draw_fov(t_cub_data *cub)
{
	int x1;
	int	y1;
	int	x;
	int	y;
	double angle;

	angle = cub->p->dir * (M_PI / 180.0);
	x1 = cub->minimap->p_img->instances[0].x + 50;
	y1 = cub->minimap->p_img->instances[0].y + 50;
	x = x1 + cos(angle) * 200;
	y = y1 + sin(angle) * 200;
	draw_line(x1, y1, x, y, cub);
}