/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:51:48 by ldick             #+#    #+#             */
/*   Updated: 2025/04/28 17:09:53 by ldick            ###   ########.fr       */
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

int	is_wall(t_cub_data *cub, int x, int y)
{
	int	map_x;
	int	map_y;

	// Translate the minimap coordinates to map coordinates
	map_x = (x) / (22);
	map_y = (y) / (22);

	// Check if the coordinates are within the map boundaries
	if (map_x < 0 || map_x >= cub->minimap->size_x || map_y < 0 || map_y >= cub->minimap->size_y)
		return (1);

	// Check if the current position is a wall
	if (cub->map[map_y][map_x] == '1')
		return (1);

	return (0);
}

unsigned int	get_pixel_color(uint8_t *p)
{
	uint32_t	b;
	uint32_t	g;
	uint32_t	r;
	uint32_t	a;

	r = *(p);
	g = *(p + 1);
	b = *(p + 2);
	a = *(p + 3);
	return (get_color(r, g, b, a));
}

bool	touch(double px, double py, t_cub_data *cub)
{
	int	x;
	int	y;

	y = py / (22);
	x = px / (22);
	cub->map_x = x;
	cub->map_y = y;
	if (x > cub->minimap->size_x || x < 0 || y < 0 || y > cub->minimap->size_y)
		return (true);
	if (!cub->map[y])
		return (true);
	if (!cub->map[y][x])
		return (true);
	if (cub->map[y][x] == '1' || cub->map[y][x] == ' ')
		return (true);
	return (false);
}

// void	draw_line_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int	dx;
// 	int	dy;
// 	int	dir;
// 	int	i;
// 	int	p;
// 	int y;

// 	i = 0;
// 	if (x0 > x1)
// 	{
// 		ft_swap(&x0, &x1, sizeof(int));
// 		ft_swap(&y0, &y1, sizeof(int));
// 	}
// 	dx = ft_abs(x1 - x0);
// 	dy = ft_abs(y1 - y0);
// 	dir = (y1 > y0) ? 1 : -1;
// 	p = 2 * dy - dx;
// 	if (dx != 0)
// 	{
// 		y = y0;
// 		while(i < dx + 1 && !touch(x0 + i - 50, y - 50, cub))
// 		{
// 			mlx_put_pixel(cub->minimap->img, x0 + i - 50, y - 50, 0x64);
// 			if (p >= 0)
// 			{
// 				y += dir;
// 				p -= 2 * dx;
// 			}
// 			p += 2 * dy;
// 			i++;
// 		}
// 	}
// }

// void	draw_line_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int	dx;
// 	int	dy;
// 	int	dir;
// 	int	i;
// 	int	p;
// 	int x;

// 	i = 0;
// 	if (y0 > y1)
// 	{
// 		ft_swap(&x0, &x1, sizeof(int));
// 		ft_swap(&y0, &y1, sizeof(int));
// 	}
// 	dx = ft_abs(x1 - x0);
// 	dy = ft_abs(y1 - y0);
// 	dir = (x1 > x0) ? 1 : -1;
// 	p = 2 * dx - dy;
// 	if (dy != 0)
// 	{
// 		x = x0;
// 		while(i < dy + 1 && !touch(x - 50, y0 + i - 50, cub))
// 		{
// 			mlx_put_pixel(cub->minimap->img, x - 50, y0 + i - 50, 0x64);
// 			if (p >= 0)
// 			{
// 				x += dir;
// 				p -= 2 * dy;
// 			}
// 			p += 2 * dx;
// 			i++;
// 		}
// 	}
// }

// void	draw_line(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);

// 	if (dx >= dy)
// 		draw_line_x(x0, y0, x1, y1, cub);  // Shallow slope
// 	else
// 		draw_line_y(x0, y0, x1, y1, cub);  // Steep slope
// }

int	draw_line_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	step_x = (dx > 0) ? 1 : -1;
	int	step_y = (dy > 0) ? 1 : -1;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
	int start_x = x0;
	int start_y = y0;
	int	p = 2 * dy - dx;
	int	i = 0;

	while (i <= dx && !touch(x0 - 50, y0 - 50, cub))
	{
		mlx_put_pixel(cub->minimap->img, x0 - 50, y0 - 50, 0x64);
		if (p >= 0)
		{
			y0 += step_y;
			p -= 2 * dx;
		}
		p += 2 * dy;
		x0 += step_x;
		i++;
	}
	double dlen = sqrt(pow(x0 - start_x, 2) + pow(y0 - start_y, 2));
	printf("%f\n", dlen);
	return (int)dlen;
}

int	draw_line_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	dx_abs = ft_abs(dx);
	int	dy_abs = ft_abs(dy);
	int	start_x = x0;
	int	start_y = y0;
	int	step_x = (dx > 0) ? 1 : -1;
	int	step_y = (dy > 0) ? 1 : -1;
	int	p = 2 * dx_abs - dy_abs;
	int	i = 0;
	while (i <= dy_abs && !touch(x0 - 50, y0 - 50, cub))
	{
		mlx_put_pixel(cub->minimap->img, x0 - 50, y0 - 50, 0x64);
		if (p >= 0)
		{
			x0 += step_x;
			p -= 2 * dy_abs;
		}
		p += 2 * dx_abs;
		y0 += step_y;
		i++;
	}
	double dlen = sqrt(pow(x0 - start_x, 2) + pow(y0 - start_y, 2));
	// printf("%f\n", dlen);
	return (int)dlen;
}

void	draw_line(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
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

	double dir_inc = (double)FOV * (M_PI / 180.0) / (double)1920;
	// double dir = atan2(cub->p->dir_y, cub->p->dir_x) - (FOV * (M_PI / 180.0)) / 2.0;
	// double dir = atan2(cub->p->dir_x, cub->p->dir_y);
	// angle = dir;
	x1 = cub->p->x;
	y1 = cub->p->y;
	x = x1 + cub->p->dir_x * 200;
	y = y1 + cub->p->dir_y * 200;
	draw_line(x1, y1, x, y, cub);
}

void	draw_fov(t_cub_data *cub)
{
	int x1;
	int y1;
	int x;
	int y;
	double angle;
	double	i;

	i = 0;
	int count = 0;
	double dir_inc = (double)FOV * (M_PI / 180.0) / (double)1920;
	double dir = atan2(cub->p->dir_y, cub->p->dir_x) - (FOV * (M_PI / 180.0)) / 2.0;
	while(i < FOV)
	{
		angle = dir;
		x1 = cub->minimap->p_img->instances[0].x + 5;
		y1 = cub->minimap->p_img->instances[0].y + 5;
		x = x1 + cos(angle) * 200;
		y = y1 + sin(angle) * 200;
		draw_line(x1, y1, x, y, cub);
		i += 1;
		dir += dir_inc;
		count++;
	}
	printf("%d\n", count);
}