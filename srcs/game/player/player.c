/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:01:07 by ldick             #+#    #+#             */
/*   Updated: 2025/02/18 18:51:53 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	collision(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x;
	y = cub->p->y;
	printf("%d--%d--%f--%f\n", (int)x, (int)y, x, y);
	printf("%c\n", cub->map[(int)(y - 0.6)][(int)x]);
	if (cub->map[(int)(y - 0.6)][(int)x] == '1')
		return (1);
	return (0);
}

void	draw_play(t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i <= PSIZE)
	{
		while(j <= PSIZE)
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
	p_start_x = (50 + (PSIZE / 2) +  (int)(cub->p->x) * 20 + (2 * cub->p->x));
	p_start_y = (50 + (PSIZE / 2) + (int)(cub->p->y) * 20 + (2 * cub->p->y));
	printf("p_start_x = %d, p_start_y = %d\n", p_start_x, p_start_y);
	cub->minimap->p_img = mlx_new_image(cub->mlx, 20, 20);
	mlx_image_to_window(cub->mlx, cub->minimap->p_img, p_start_x, p_start_y);
	printf("p_img_x = %d, p_img_y = %d\n", cub->minimap->p_img->instances[0].x, cub->minimap->p_img->instances[0].y);
	draw_play(cub);
	return ;
}