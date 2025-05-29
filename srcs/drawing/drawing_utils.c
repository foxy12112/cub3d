/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:55:42 by ldick             #+#    #+#             */
/*   Updated: 2025/05/29 16:56:08 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(double px, double py, t_cub_data *cub)
{
	int	x;
	int	y;

	y = py / (22);
	x = px / (22);
	if (x > cub->map_width || x < 0 || y < 0 || y > cub->map_height)
		return (true);
	if (!cub->map[y])
		return (true);
	if (!cub->map[y][x])
		return (true);
	if (cub->map[y][x] == '1' || cub->map[y][x] == ' ')
		return (true);
	return (false);
}

int	draw_line_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	step_x = (dx > 0) ? 1 : -1;
	int	step_y = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	int start_x = x0;
	int start_y = y0;
	int	p = 2 * dy - dx;
	int	i = 0;

	while (i <= dx && !touch(x0, y0, cub))
	{
		mlx_put_pixel(cub->omg, x0, y0, 0xffffffff);
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
	// printf("%f\n", dlen);
	return (int)dlen;
}

int	draw_line_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	dx_abs = abs(dx);
	int	dy_abs = abs(dy);
	int	start_x = x0;
	int	start_y = y0;
	int	step_x = (dx > 0) ? 1 : -1;
	int	step_y = (dy > 0) ? 1 : -1;
	int	p = 2 * dx_abs - dy_abs;
	int	i = 0;
	while (i <= dy_abs && !touch(x0, y0, cub))
	{
		mlx_put_pixel(cub->omg, x0, y0, 0xffffffff);
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

void	bresenham(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
		draw_line_x(x0, y0, x1, y1, cub);
	else
		draw_line_y(x0, y0, x1, y1, cub);
}

unsigned int	get_pixel_color(uint8_t *p)
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;

	r = *(p + 0);
	g = *(p + 1);
	b = *(p + 2);
	a = *(p + 3);
	return (r << 24 | g << 16 | b << 8 | a);
}
