/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:55:42 by ldick             #+#    #+#             */
/*   Updated: 2025/05/31 15:28:31 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_pixel_color(uint8_t *p)
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;

	r = *(p + 0);
	g = *(p + 1);
	b = *(p + 2);
	a = *(p + 3);
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_player(t_cub_data *cub)
{
	int	x;
	int	y;

	y = -5;
	while (y < 5)
	{
		x = -5;
		while (x < 5)
		{
			mlx_put_pixel(cub->img, cub->player_x * 22 + x,
				cub->player_y * 22 + y, 0xcbc3e3ff);
			x++;
		}
		y++;
	}
}
