/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:16:37 by ldick             #+#    #+#             */
/*   Updated: 2025/04/10 10:19:05 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*rm_s(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
		i++;
	if (i == len)
	{
		str[0] = '\0';
		return (str);
	}
	while (i < len)
		str[j++] = str[i++];
	str[j] = '\0';
	len = ft_strlen(str) - 1;
	while (len >= 0 && (str[len] == ' ' || str[len] == '\t'
			|| str[len] == '\n' || str[len] == '\r'))
		str[len--] = '\0';
	return (str);
}

mlx_texture_t	*scale_tex(mlx_texture_t *texture, int width, int height)
{
	mlx_texture_t	*dst;

	dst = malloc(sizeof(mlx_texture_t));
	if (!dst)
		return (NULL);
	dst->width = width;
	dst->height = height;
	dst->pixels = malloc(width * height * 4);
	if (!dst->pixels)
	{
		free(dst);
		return (NULL);
	}
	dst->bytes_per_pixel = 4;
	scale(dst, texture, width, height);
	return (dst);
}

void	*create_image(t_cub_data *cub, char *str)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(str);
	if (!texture)
	{
		ft_error(cub, "Error opening text:");
	}
	texture = scale_tex(texture, 1024, 1024);
	if (!texture)
		ft_error(cub, "Scaling failed");
	image = mlx_texture_to_image(cub->mlx, texture);
	if (!image)
		ft_error(cub, "Texture to image failed");
	mlx_delete_texture(texture);
	return (image);
}

int	get_color(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
