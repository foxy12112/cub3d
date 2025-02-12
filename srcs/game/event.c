/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:30:21 by ldick             #+#    #+#             */
/*   Updated: 2025/02/12 18:27:18 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_event(mlx_key_data_t mkd, void *param)
{
	t_cub_data *cub = (t_cub_data *)param;

	if (mkd.key == MLX_KEY_W)
		cub->p->y += 0.5;
	else if (mkd.key == MLX_KEY_S)
		cub->p->y -= 0.5;
	if (mkd.key == MLX_KEY_A)
		cub->p->x -= 0.5;
	else if (mkd.key == MLX_KEY_D)
		cub->p->x += 0.5;
}

void	event_handler(mlx_key_data_t mkd, void *param)
{
	t_cub_data *cub = (t_cub_data *)param;

	if (mkd.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(cub->mlx);
		exit(EXIT_SUCCESS);
	}
	else if (mkd.key == MLX_KEY_9)
		mlx_set_window_size(cub->mlx, cub->mlx->width + 1, cub->mlx->height);
	else if (mkd.key == MLX_KEY_8)
		mlx_set_window_size(cub->mlx, cub->mlx->width, cub->mlx->height + 1);
	else if (mkd.key == MLX_KEY_KP_SUBTRACT)
		mlx_set_window_size(cub->mlx, cub->mlx->width - 10, cub->mlx->height - 10);
}

// void	minimap_event(mlx_key_data_t mkd, void *param)
// {
// 	t_cub_data *cub = (t_cub_data *)param;
// 	if (mkd.key == MLX_KEY_W)
// 		cub->minimap->p_img->instances[0].y -= 5;
// 	else if (mkd.key == MLX_KEY_S)
// 		cub->minimap->p_img->instances[0].y += 5;
// 	if (mkd.key == MLX_KEY_A)
// 		cub->minimap->p_img->instances[0].x -= 5;
// 	else if (mkd.key == MLX_KEY_D)
// 		cub->minimap->p_img->instances[0].x += 5;
// }

void	event(mlx_key_data_t mkd, void *param)
{
	event_handler(mkd, param);
	player_event(mkd, param);
	// minimap_event(mkd, param);
}