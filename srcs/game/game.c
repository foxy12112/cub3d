/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/02/07 17:13:33 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(mlx_t *mlx, t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("%d--%d\n", mlx->height, mlx->width);
	while(i < mlx->height)
	{
		while(j < mlx->width)
		{
			mlx_put_pixel(cub->mlx->img, i, j, cub->ceiling);
			j++;
		}
		j = 0;
		i++;
	}
}

void resize_callback(int32_t width, int32_t height, void* param)
{
	t_cub_data *cub = param;
	draw(cub->mlx->mlx, cub);
	printf("Window resized to width: %d, height: %d\n", width, height);
}

void	game_loop(t_cub_data *cub)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	cub->mlx->mlx = mlx_init(cub->mlx->width, cub->mlx->height, "cub3d", true);
	cub->ceiling = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 255);
	cub->mlx->img = mlx_new_image(cub->mlx->mlx, cub->mlx->mlx->height, cub->mlx->mlx->width);
	mlx_image_to_window(cub->mlx->mlx, cub->mlx->img, 0, 0);
	// draw(cub, 256, 256);
	mlx_resize_hook(cub->mlx->mlx, &resize_callback, cub);
	mlx_key_hook(cub->mlx->mlx, event_handler, cub);
	mlx_loop(cub->mlx->mlx);
	mlx_terminate(cub->mlx->mlx);
}