/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/02/21 09:57:34 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_c_f(t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

void ft_hook(void* param)
{
    t_cub_data* cub = (t_cub_data*)param;
    double move_speed = 1.0;

	// Handle player movement
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP) && !collision_top(cub))
		cub->minimap->p_img->instances[0].y -= move_speed; // Move up on minimap
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN) && !collision_bottom(cub))
		cub->minimap->p_img->instances[0].y += move_speed; // Move down on minimap
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) && !collision_left(cub))
		cub->minimap->p_img->instances[0].x -= move_speed; // Move left on minimap
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT) && !collision_right(cub))
		cub->minimap->p_img->instances[0].x += move_speed; // Move right on minimap
	cub->p->x = (double)(cub->minimap->p_img->instances[0].x - 50) / (double)(22);
	cub->p->y = (double)(cub->minimap->p_img->instances[0].y - 50) / (double)(22);
	printf("Actual position: (%.2f, %.2f)\n", cub->p->x, cub->p->y);
}

void	game_loop(t_cub_data *cub)
{
	cub->ceiling = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 255);
	cub->floor = get_color(cub->texture->floor->r, cub->texture->floor->g, cub->texture->floor->b, 255);
	cub->img = mlx_new_image(cub->mlx, 2880, 1620);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	cub->img->instances->z = 0;
	draw_c_f(cub);
	map(cub);
	draw_player(cub);
	mlx_image_to_window(cub->mlx, cub->texture->no_tex, 50, 50);
	mlx_key_hook(cub->mlx, event, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}