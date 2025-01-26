/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/01/26 15:23:52 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(t_cub_data *cub)
{
	cub->mlx->mlx = mlx_init(256, 256, "cub3d", true);
	int	c = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 0);
	int i = 0;
	int j = 0;
	cub->mlx->img = mlx_new_image(cub->mlx->mlx, 256, 256);
	while(i < 256)
	{
		while(j < 256)
		{
			mlx_put_pixel(cub->mlx->img, j, i, c);
		}
		j = 0;
		i++;
	}
	mlx_image_to_window(cub->mlx->mlx, cub->mlx->img, 0, 0);
	mlx_loop(cub->mlx->mlx);
}