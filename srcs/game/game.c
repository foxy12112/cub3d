/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/02/28 17:24:28 by ldick            ###   ########.fr       */
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
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) && !collision_top(cub))
		cub->minimap->p_img->instances[0].y -= move_speed; // Move up on minimap
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) && !collision_bottom(cub))
		cub->minimap->p_img->instances[0].y += move_speed; // Move down on minimap
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A) && !collision_left(cub))
		cub->minimap->p_img->instances[0].x -= move_speed; // Move left on minimap
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D) && !collision_right(cub))
		cub->minimap->p_img->instances[0].x += move_speed; // Move right on minimap
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->p->dir--;
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->p->dir++;
	if (cub->p->dir > 360)
		cub->p->dir = 0;
	if (cub->p->dir < 0)
		cub->p->dir = 360;
	cub->p->x = (double)(cub->minimap->p_img->instances[0].x - 50) / (double)(22);
	cub->p->y = (double)(cub->minimap->p_img->instances[0].y - 50) / (double)(22);
	// printf("Actual position: (%.2f, %.2f)\n", cub->p->x, cub->p->y);
	draw_ray(cub);
	printf("%.5f\n", cub->p->dir);
}

void	game_loop(t_cub_data *cub)
{
	cub->ceiling = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 255);
	cub->floor = get_color(cub->texture->floor->r, cub->texture->floor->g, cub->texture->floor->b, 255);
	cub->img = mlx_new_image(cub->mlx, cub->mlx->width, cub->mlx->height);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	cub->img->instances->z = 0;
	draw_c_f(cub);
	map(cub);
	draw_player(cub);
	mlx_key_hook(cub->mlx, event, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}