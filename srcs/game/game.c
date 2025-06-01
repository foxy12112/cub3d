/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:01:16 by ldick             #+#    #+#             */
/*   Updated: 2025/06/01 13:52:22 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_cub_data	*cub;

	cub = (t_cub_data *)param;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_RELEASE)
	{
		cub->player_x = cub->player_start_x;
		cub->player_y = cub->player_start_y;
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_RELEASE)
		cub->mouse_on_off = !cub->mouse_on_off;
}

int	game(t_cub_data *cub)
{
	cub->img = mlx_new_image(cub->mlx, WIDHT, HEIGHT);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub->mlx, HEIGHT / 2, WIDHT / 2);
	mlx_key_hook(cub->mlx, &keyhook, cub);
	mlx_loop_hook(cub->mlx, &events, cub);
	mlx_loop(cub->mlx);
	return (0);
}
