/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:51:48 by ldick             #+#    #+#             */
/*   Updated: 2025/02/20 17:41:54 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_pixels(uint8_t *dst, uint8_t *src)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = src[3];
}

void	scale(mlx_texture_t *new, mlx_texture_t *tex, int width, int height)
{
	int	x;
	int	y;
	int	src;
	int	dst;
	int	temp;

	y = 0;
	while(y < height)
	{
		x = 0;
		while(x < width)
		{
			temp = x * tex->width / width;
			src = ((y * tex->height / height) * tex->width + temp) * 4;
			dst = (y * width + x) * 4;
			copy_pixels(&new->pixels[dst], &tex->pixels[src]);
			x++;
		}
		y++;
	}
}
