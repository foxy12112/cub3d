/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/02/08 16:02:57 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_c_f(t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("%d--%d\n", cub->mlx->height, cub->mlx->width);
	while(i < cub->mlx->height / 2)
	{
		while(j < cub->mlx->width)
		{
			mlx_put_pixel(cub->img, j, i, cub->ceiling);
			j++;
		}
		j = 0;
		i++;
	}
	while(i < cub->mlx->height)
	{
		while(j < cub->mlx->width)
		{
			mlx_put_pixel(cub->img, j, i, cub->floor);
			j++;
		}
		j = 0;
		i++;
	}
}

void resize_callback(int32_t width, int32_t height, void* param)
{
	t_cub_data *cub = param;
	draw_c_f(cub);
	printf("Window resized to width: %d, height: %d\n", width, height);
}

// void	add_images(t_cub_data *cub)
// {
// 
// }

void	game_loop(t_cub_data *cub)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	image = NULL;
	mlx_set_setting(MLX_MAXIMIZED, true);
	cub->mlx = mlx_init(2880, 1620, "cub3d", true);
	cub->ceiling = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 255);
	cub->floor = get_color(cub->texture->floor->r, cub->texture->floor->g, cub->texture->floor->b, 255);
	cub->img = mlx_new_image(cub->mlx, 2880, 1620);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	// add_images(cub);
	// draw(cub, 256, 256);
	texture = mlx_load_png("textures/arctic_Monkeys.png");
	image	= mlx_texture_to_image(cub->mlx, texture);
	mlx_image_to_window(cub->mlx, image, 50, 50);
	mlx_resize_hook(cub->mlx, &resize_callback, cub);
	mlx_key_hook(cub->mlx, event_handler, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}