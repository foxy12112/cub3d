/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:30:21 by ldick             #+#    #+#             */
/*   Updated: 2025/02/07 17:09:16 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_handler(mlx_key_data_t mkd, void *param)
{
	t_cub_data *cub = (t_cub_data *)param;

	if (mkd.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(cub->mlx->mlx);
		exit(EXIT_SUCCESS);
	}
	else if (mkd.key == MLX_KEY_9)
		mlx_set_window_size(cub->mlx->mlx, cub->mlx->mlx->width + 1, cub->mlx->mlx->height);
	else if (mkd.key == MLX_KEY_8)
		mlx_set_window_size(cub->mlx->mlx, cub->mlx->mlx->width, cub->mlx->mlx->height + 1);
	else if (mkd.key == MLX_KEY_KP_SUBTRACT)
		mlx_set_window_size(cub->mlx->mlx, cub->mlx->mlx->width - 10, cub->mlx->mlx->height - 10);
}