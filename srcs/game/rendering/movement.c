// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   movement.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/22 16:09:17 by ldick             #+#    #+#             */
// /*   Updated: 2025/03/22 16:35:40 by ldick            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub3d.h"

static void	ray_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	double	step_x = (dx > 0) ? 2 : -2;
	double	step_y = (dy > 0) ? 2 : -2;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
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
		cub->move->x[i] = x0 - 50;
		cub->move->y[i] = y0 - 50;
		printf("%d--%d--%d\n", y0 - 50, x0 - 50, i);
		i++;
	}
}

static void	ray_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	dx_abs = ft_abs(dx);
	int	dy_abs = ft_abs(dy);
	double	step_x = (dx > 0) ? 2 : -2;
	double	step_y = (dy > 0) ? 2 : -2;
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
		cub->move->x[i] = x0 - 50;
		cub->move->y[i] = y0 - 50;
		i++;
	}
}

static void	teleport(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
		ray_x(x0, y0, x1, y1, cub);
	else
		ray_y(x0, y0, x1, y1, cub);
}

void	calc_location(t_cub_data *cub)
{
	double	angle;
	int		x;
	int		y;
	int		x1;
	int		y1;

	angle = cub->p->dir * (M_PI / 180);
	x1 = cub->minimap->p_img->instances[0].x + 5;
	y1 = cub->minimap->p_img->instances[0].y + 5;
	x = x1 + cos(angle - M_PI_2) * 29;
	y = y1 + sin(angle - M_PI_2) * 29;
	teleport(x1, y1, x, y, cub);
	x = 0;
	while(x < 29)
	{
		if (cub->move->x[x] < 0 || cub->move->y[x] < 0)
		{
			cub->move->x[x] = cub->move->x[x - 1];
			cub->move->y[x] = cub->move->y[x - 1];
		}
		x++;
	}
}
