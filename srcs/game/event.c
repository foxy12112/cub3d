/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:30:21 by ldick             #+#    #+#             */
/*   Updated: 2025/03/17 14:33:50 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	player_event(mlx_key_data_t mkd, void *param)
// {
// 	t_cub_data	*cub;

// 	cub = (t_cub_data *)param;
// 	(void)mkd;
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
// 		cub->p->y += 0.5;
// 	else if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
// 		cub->p->y -= 0.5;
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
// 		cub->p->x -= 0.5;
// 	else if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
// 		cub->p->x += 0.5;
// }

// void	player_event(t_cub_data *cub)
// {
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
// 		cub->p->y += 0.5;
// 	else if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
// 		cub->p->y -= 0.5;
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
// 		cub->p->x -= 0.5;
// 	else if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
// 		cub->p->x += 0.5;
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
// 	{
// 		mlx_terminate(cub->mlx);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else if (mlx_is_key_down(cub->mlx, MLX_KEY_9))
// 		mlx_set_window_size(cub->mlx, cub->mlx->width + 1, cub->mlx->height);
// 	else if (mlx_is_key_down(cub->mlx, MLX_KEY_8))
// 		mlx_set_window_size(cub->mlx, cub->mlx->width, cub->mlx->height + 1);
// 	else if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_SUBTRACT))
// 		mlx_set_window_size(cub->mlx, cub->mlx->width - 10, cub->mlx->height
// 			- 10);
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_O) && mkd.action != MLX_RELEASE)
// 		draw_fov(cub);
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_0) && mkd.action != MLX_RELEASE)
// 		draw_ray(cub);
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_ENTER) && mkd.action != MLX_RELEASE)
// 		raytrace(cub);
// }

void	event_handler(mlx_key_data_t mkd, void *param)
{
	t_cub_data	*cub;

	cub = (t_cub_data *)param;
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
		mlx_set_window_size(cub->mlx, cub->mlx->width - 10, cub->mlx->height
			- 10);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_O) && mkd.action != MLX_RELEASE)
		draw_fov(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_0) && mkd.action != MLX_RELEASE)
		draw_ray(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_ENTER) && mkd.action != MLX_RELEASE)
		raytrace(cub);
}

void	event(mlx_key_data_t mkd, void *param)
{
	event_handler(mkd, param);
	// player_event(mkd, param);
}