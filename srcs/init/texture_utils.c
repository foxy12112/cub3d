/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:36:40 by ldick             #+#    #+#             */
/*   Updated: 2025/06/02 13:54:16 by ldick            ###   ########.fr       */
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

void	scale(mlx_texture_t *new, mlx_texture_t *old)
{
	int	x;
	int	y;
	int	src;
	int	dst;
	int	temp;

	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			temp = x * old->width / TEX_WIDTH;
			src = ((y * old->height / TEX_HEIGHT) * old->width + temp) * 4;
			dst = (y * TEX_WIDTH + x) * 4;
			copy_pixels(&new->pixels[dst], &old->pixels[src]);
			x++;
		}
		y++;
	}
}

mlx_texture_t	*correct_texture(char *line)
{
	mlx_texture_t	*tex;
	mlx_texture_t	*scaled;

	line = rm_s(line);
	tex = mlx_load_png(line);
	if (!tex)
		return (NULL);
	scaled = malloc(sizeof(mlx_texture_t));
	if (!scaled)
		return (NULL);
	scaled->width = TEX_WIDTH;
	scaled->height = TEX_HEIGHT;
	scaled->bytes_per_pixel = 4;
	scaled->pixels = malloc(TEX_WIDTH * TEX_HEIGHT * 4);
	if (!scaled->pixels)
		return (free(scaled), NULL);
	scale(scaled, tex);
	mlx_delete_texture(tex);
	return (scaled);
}
