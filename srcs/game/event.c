/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:09 by ldick             #+#    #+#             */
/*   Updated: 2025/05/30 19:21:50 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_cub_data *cub, int x, int y)
{
	int	i;

	i = 0;
	while (i < RECTANGLE)
	{
		mlx_put_pixel(cub->img, (x + 1) * (RECTANGLE + 2) - 2, y * (RECTANGLE
				+ 2) + i, 0x545454fa);
		mlx_put_pixel(cub->img, (x + 1) * (RECTANGLE + 2) - 1, y * (RECTANGLE
				+ 2) + i, 0x545454fa);
		i++;
	}
	i = 0;
	while (i < RECTANGLE)
	{
		mlx_put_pixel(cub->img, x * (RECTANGLE + 2) + i, (y + 1) * (RECTANGLE
				+ 2) - 2, 0x545454fa);
		mlx_put_pixel(cub->img, x * (RECTANGLE + 2) + i, (y + 1) * (RECTANGLE
				+ 2) - 1, 0x545454fa);
		i++;
	}
}

void	draw_square(t_cub_data *cub, int wall, int x, int y)
{
	int	color;
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (wall)
		color = 0xb56641ff;
	else
		color = 0x747878ff;
	draw_wall(cub, x, y);
	while (i < RECTANGLE)
	{
		while (j < RECTANGLE)
		{
			mlx_put_pixel(cub->img, x * (RECTANGLE + 2) + i, y * (RECTANGLE + 2)
				+ j, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_map(t_cub_data *cub)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (cub->map[y])
	{
		while (cub->map[y][x])
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

void	exit_game(t_cub_data *cub)
{
	free_split(cub->map);
	free(cub->map);
	mlx_delete_texture(cub->texture_north);
	mlx_delete_texture(cub->texture_south);
	mlx_delete_texture(cub->texture_east);
	mlx_delete_texture(cub->texture_west);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_delete_image(cub->mlx, cub->omg);
	mlx_terminate(cub->mlx);
	free(cub);
	exit(0);
}

void	events(void *param)
{
	t_cub_data	*cub;

	cub = (t_cub_data *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		exit_game(cub);
	movement(cub);
	movement_vertical(cub);
	rotate(cub, 0);
	mouse(cub);
	draw_background(cub);
	dda_loop(cub);
	draw_map(cub);
	draw_player(cub);
}
