/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:01:16 by ldick             #+#    #+#             */
/*   Updated: 2025/05/28 14:59:11 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game(t_cub_data *cub)
{
	cub->img = mlx_new_image(cub->mlx, WIDHT, HEIGHT);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	cub->omg = mlx_new_image(cub->mlx, WIDHT, HEIGHT);
	mlx_image_to_window(cub->mlx, cub->omg, 0, 0);
	cub->omg->instances->z = 1;
	// calculate_map(cub);
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub->mlx, HEIGHT / 2, WIDHT / 2);
	mlx_loop_hook(cub->mlx, &events, cub);
	mlx_loop(cub->mlx);
	return (0);
}