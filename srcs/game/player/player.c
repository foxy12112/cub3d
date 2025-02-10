/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:01:07 by ldick             #+#    #+#             */
/*   Updated: 2025/02/10 18:36:06 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	track_player(t_cub_data *cub)
// {
	
// }

// static void	put_circle_pixel(int cx, int y, int cy, int x, t_cub_data *cub)
// {
// 	mlx_put_pixel(cub->img, cx + x, cy + y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx - x, cy + y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx + x, cy - y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx - x, cy - y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx + x, cy + y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx + x, cy - y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx - x, cy + y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx - x, cy - y, 0xfffff);
// }

static void	draw_circle(t_cub_data *cub, int cx, int cy, int r)
{
	int x;
	int y;
	int p;

	p = r * -1;
	x = 0;
	y = r * -1;
	while(x < -y)
	{
		if (p > 0)
		{
			y++;
			p += x*y*2 + 1;
		}
		else
			p += 2*x + 1;
		mlx_put_pixel(cub->img, cx + x, cy + y, 0xfffff);
		mlx_put_pixel(cub->img, cx - x, cy + y, 0xfffff);
		mlx_put_pixel(cub->img, cx + x, cy - y, 0xfffff);
		mlx_put_pixel(cub->img, cx - x, cy - y, 0xfffff);
		mlx_put_pixel(cub->img, cx + x, cy + y, 0xfffff);
		mlx_put_pixel(cub->img, cx + x, cy - y, 0xfffff);
		mlx_put_pixel(cub->img, cx - x, cy + y, 0xfffff);
		mlx_put_pixel(cub->img, cx - x, cy - y, 0xfffff);
		x++;
	}
}

void	draw_player(t_cub_data *cub)
{
	draw_circle(cub, 500, 500, 50);
	return ;
}