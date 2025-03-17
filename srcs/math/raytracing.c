/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:29:42 by ldick             #+#    #+#             */
/*   Updated: 2025/03/17 15:29:11 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ray_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
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

static int	ray_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
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

static int	ray(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
		return (ray_x(x0, y0, x1, y1, cub));
	else
		return(ray_y(x0, y0, x1, y1, cub));
}

void	draw_v_line(int x, int start, int end, mlx_image_t *img)
{
	while(start++ <= end)
		mlx_put_pixel(img, x, start, 0x4514ffff);
}

void	draw_game(int x, int ray_d, t_cub_data *cub)
{
	int line_hight = (cub->img->height * (cub->minimap->img->height / ray_d));
	printf("%d--", ray_d);
	printf("%d\n", line_hight);
	int	draw_start = (-line_hight / 2) + (cub->img->height / 2);
	draw_start = (draw_start < 0) ? 0 : draw_start;
	int draw_end = (line_hight / 2) + (cub->img->height / 2);
	if (draw_end >= cub->mlx->height)
		draw_end = cub->mlx->height - 1;
	// ft_swap(&draw_end, &draw_start, sizeof(int));
	// printf("%d--%d--%d--%d\n", x, draw_start, draw_end, 1);
	// printf("%d--%d\n", draw_end, draw_start);
	draw_v_line(x, draw_start, draw_end, cub->img);
}

int	raytrace(t_cub_data *cub)
{
	int x1;
	int y1;
	int x;
	int y;
	double angle;
	double	i;
	double dir;
	int temp = 0;
	dir = cub->p->dir;
	i = 0;
	int tmp;
	draw_c_f(cub);
	while(i < (double)FOV)
	{
		angle = dir * (M_PI / 180);
		x1 = cub->minimap->p_img->instances[0].x + 5;
		y1 = cub->minimap->p_img->instances[0].y + 5;
		x = x1 + cos(angle - M_PI_2) * 200;
		y = y1 + sin(angle - M_PI_2) * 200;
		int ray_d = ray(x1, y1, x, y, cub);
		printf("ray-length=%d--ray_number=%0f\n", ray_d, i);
		tmp = temp + (cub->mlx->width / FOV);
		while(temp < tmp)
		{
			// printf("%d--%d\n", temp, tmp);
			draw_game(temp, ray_d, cub);
			temp++;
		}
		i += 1;
		dir += 0.5;
	}
	return (1);
}

