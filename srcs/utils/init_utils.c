/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:16:37 by ldick             #+#    #+#             */
/*   Updated: 2025/04/09 14:19:15 by ldick            ###   ########.fr       */
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

int	add_texture(int i, t_texture_data *texture, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		texture->no = ft_strdup(line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		texture->so = ft_strdup(line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		texture->we = ft_strdup(line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		texture->ea = ft_strdup(line + 2);
	else if (ft_strncmp(line, "F", 1) == 0)
		texture->floor->floor = ft_strdup(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		texture->ceiling->ceiling = ft_strdup(line + 1);
	else if ((line)[0] == '\n')
		return (i);
	else
		return (720);
	return (i + 1);
}

int	init_map(t_cub_data *cub, int fd)
{
	char	*newline;
	int		i;
	char	*line;

	line = get_next_line(fd);
	i = 0;
	cub->map = safe_malloc(sizeof (char *) * 1024, cub, __func__);
	while (line)
	{
		if ((int)ft_strlen(line) > cub->minimap->size_x)
			cub->minimap->size_x = (int)ft_strlen(line);
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		cub->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		cub->minimap->size_y++;
	}
	cub->map[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_color(t_texture_data *texture)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(texture->ceiling->ceiling, ',');
	texture->ceiling->r = ft_atoi(tmp[0]);
	texture->ceiling->g = ft_atoi(tmp[1]);
	texture->ceiling->b = ft_atoi(tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	tmp = ft_split(texture->floor->floor, ',');
	texture->floor->r = ft_atoi(tmp[0]);
	texture->floor->g = ft_atoi(tmp[1]);
	texture->floor->b = ft_atoi(tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	return (1);
}