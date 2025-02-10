/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:08:20 by ldick             #+#    #+#             */
/*   Updated: 2025/02/10 17:04:43 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_square(t_cub_data *cub, int wall, int x, int y)
{
	int color;
	int rect_size;

	rect_size = 20;
	if (wall == 1)
		color = 0xffffff;
	else
		color = 0xf0160a;
	int i = 0;
	while (i < rect_size)
	{
		int j = 0;
		while (j < rect_size)
		{
			mlx_put_pixel(cub->minimap->img, x * rect_size + i, y * rect_size + j, color);
			j++;
		}
		i++;
	}
}


void	draw_map(t_cub_data *cub)
{
	int x;
	int y;

	y = 0;
	x = 0;
	while(cub->map[y])
	{
		while(cub->map[y][x])
		{
			if (cub->map[y][x] == '1' || cub->map[y][x] == ' ')
				draw_square(cub, 1, x, y);
			else
				draw_square(cub, 0, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	map(t_cub_data *cub)
{
	cub->minimap->img = mlx_new_image(cub->mlx, 1000, 2000);
	mlx_image_to_window(cub->mlx, cub->minimap->img, 50, 50);
	draw_map(cub);
	cub->p->x = (float)cub->p->start_x;
	cub->p->y = (float)cub->p->start_y;
	printf("%.6f,--%.6f\n", cub->p->x, cub->p->y);
}