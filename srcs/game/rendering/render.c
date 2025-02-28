/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:51:48 by ldick             #+#    #+#             */
/*   Updated: 2025/02/28 17:24:21 by ldick            ###   ########.fr       */
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

void	draw_line_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
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
	dx = ft_abs(x1 - x0);
	dy = ft_abs(y1 - y0);
	dir = (y1 > y0) ? 1 : -1;
	p = 2 * dy - dx;
	if (dx != 0)
	{
		y = y0;
		while(i < dx + 1)
		{
			mlx_put_pixel(cub->img, x0 + i, y, 0x64);
			if (p >= 0)
			{
				y += dir;
				p -= 2 * dx;
			}
			p += 2 * dy;
			i++;
		}
	}
}

void	draw_line_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx;
	int	dy;
	int	dir;
	int	i;
	int	p;
	int x;

	i = 0;
	if (y0 > y1)
	{
		ft_swap(&x0, &x1, sizeof(int));
		ft_swap(&y0, &y1, sizeof(int));
	}
	dx = ft_abs(x1 - x0);
	dy = ft_abs(y1 - y0);
	dir = (x1 > x0) ? 1 : -1;
	p = 2 * dx - dy;
	if (dy != 0)
	{
		x = x0;
		while(i < dy + 1)
		{
			mlx_put_pixel(cub->img, x, y0 + i, 0x64);
			if (p >= 0)
			{
				x += dir;
				p -= 2 * dy;
			}
			p += 2 * dx;
			i++;
		}
	}
}

void	draw_line(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	if (ft_abs(x1-x0) > ft_abs(y1-y0))
		draw_line_x(x0, y0, x1, y1, cub);
	else
		draw_line_y(x0, y0, x1, y1, cub);
}

void	draw_ray(t_cub_data *cub)
{
	int x1;
	int	y1;
	int	x;
	int	y;
	double angle;

	angle = cub->p->dir * (M_PI / 180);
	x1 = cub->minimap->p_img->instances[0].x + 5;
	y1 = cub->minimap->p_img->instances[0].y + 5;
	x = x1 + cos(angle - M_PI_2) * 200;
	y = y1 + sin(angle - M_PI_2) * 200;
	draw_line(x1, y1, x, y, cub);
}
