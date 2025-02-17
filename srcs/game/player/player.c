/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:01:07 by ldick             #+#    #+#             */
/*   Updated: 2025/02/17 18:11:13 by ldick            ###   ########.fr       */
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
	int	p_start_x;
	int	p_start_y;
	// 160, 240;
	p_start_x = (50 + (int)(cub->p->x) * 20);
	p_start_y = (50 + (int)(cub->p->y) * 20);
	printf("p_start_x = %d, p_start_y = %d\n", p_start_x, p_start_y);
	cub->minimap->p_img = mlx_new_image(cub->mlx, 20, 20);
	mlx_image_to_window(cub->mlx, cub->minimap->p_img, p_start_x, p_start_y);
	printf("p_img_x = %d, p_img_y = %d\n", cub->minimap->p_img->instances[0].x, cub->minimap->p_img->instances[0].y);
	draw_play(cub);
	return ;
}