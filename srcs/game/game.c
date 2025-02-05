/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/02/05 19:03:23 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < cub->mlx->height)
	{
		while(j < cub->mlx->width)
		{
			mlx_put_pixel(cub->mlx->img, j, i, cub->ceiling);
			j++;
		}
		j = 0;
		i++;
	}
}

void resize_callback(int32_t width, int32_t height, void* param)
{
	t_cub_data *cub = (t_cub_data*)param;
	cub->mlx->height = (int)height;
	cub->mlx->width = (int)width;
	draw(cub);
	printf("Window resized to width: %d, height: %d\n", width, height);
}


void	game_loop(t_cub_data *cub)
{
	cub->mlx->mlx = mlx_init(cub->mlx->width, cub->mlx->height, "cub3d", true);
	cub->ceiling = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 255);
	cub->mlx->img = mlx_new_image(cub->mlx->mlx, 256, 256);
	mlx_image_to_window(cub->mlx->mlx, cub->mlx->img, 0, 0);
	// draw(cub);
	// mlx_resize_hook(cub->mlx->mlx, &resize_callback, cub);
	mlx_loop(cub->mlx->mlx);
	mlx_terminate(cub->mlx->mlx);
}