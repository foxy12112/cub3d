/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 07:58:04 by ldick             #+#    #+#             */
/*   Updated: 2025/02/13 12:45:12 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_box(t_cub_data *cub)
{
	uint32_t	x;
	uint32_t	y;
	int	color;

	color = get_color(84, 84, 84, 240);
	y = 0;
	x = 0;
	while(x < cub->text->img->width)
	{
		while(y < cub->text->img->height)
		{
			mlx_put_pixel(cub->text->img, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
}

void	draw_textbox(t_cub_data *cub)
{
	cub->text->img = mlx_new_image(cub->mlx, 1000, 30);
	mlx_image_to_window(cub->mlx, cub->text->img, 20, cub->img->height - 100);
	if (cub->text->active == 2)
		mlx_put_string(cub->mlx, cub->text->text, cub->text->img->instances[0].x + 5, cub->text->img->instances[0].y + 5);
	draw_box(cub);
}