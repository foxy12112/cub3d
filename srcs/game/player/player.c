/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:01:07 by ldick             #+#    #+#             */
/*   Updated: 2025/02/12 16:24:39 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	track_player(t_cub_data *cub)
// {
	
// }

// static void	put_circle_pixel(int cx, int y, int cy, int x, t_cub_data *cub)
// {
// 	mlx_put_pixel(cub->img, cx + x, cy + y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx - x, cy + y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx + x, cy - y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx - x, cy - y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx + x, cy + y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx + x, cy - y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx - x, cy + y, 0xfffff);
// 	mlx_put_pixel(cub->img, cx - x, cy - y, 0xfffff);
// }

void	draw_play(t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i <= 20)
	{
		while(j <= 20)
		{
			mlx_put_pixel(cub->minimap->p_img, i, j, 0xfffff);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_player(t_cub_data *cub)
{
	cub->minimap->p_img = mlx_new_image(cub->mlx, 20, 20);
	mlx_image_to_window(cub->mlx, cub->minimap->p_img, 130, 220);
	draw_play(cub);
	return ;
}