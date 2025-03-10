/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:16:37 by ldick             #+#    #+#             */
/*   Updated: 2025/03/10 09:40:24 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

char	*rm_s(char *str)
{
	int		i;
	int		j;
	int		lenght;

	lenght = ft_strlen(str);
	i = 0;
	j = 0;
	while (i < lenght)
	{
		if (str[i] != ' ')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

mlx_texture_t	*scale_tex(mlx_texture_t *texture, int width, int height)
{
	mlx_texture_t	*dst;
	
	dst = malloc(sizeof(mlx_texture_t));
	if (!dst)
		return (NULL); //change functino for ft_error
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

	texture = scale_tex(mlx_load_png(str), 1024, 1024);
	if (!texture)
		ft_error(cub, "scaling failed");
	image = mlx_texture_to_image(cub->mlx, texture);
	if (!image)
		ft_error(cub, "texture to image failed");
	mlx_delete_texture(texture);
	return (image);
}


int	get_color(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24 | (g & 0xff) << 16 | (b & 0xff) << 8 | (a & 0xff) << 0);
}

