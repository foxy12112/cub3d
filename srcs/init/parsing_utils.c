/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:08:22 by ldick             #+#    #+#             */
/*   Updated: 2025/05/29 16:06:22 by ldick            ###   ########.fr       */
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
		while(x < TEX_WIDTH)
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

mlx_texture_t	*correct_texture(char *line, int *i)
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
	*i += 1;
	return (scaled);
}

int		ft_isnum(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
} //TODO fix

int		get_background(char *line, int *i)
{
	char	**tmp;
	int		color;

	tmp = ft_split(line, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
		return (0);
	color = get_color(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]), 255);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	*i += 1;
	if (!color)
		return (0);
	return (color);
}

int	add_textures(t_cub_data *cub)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(cub->map_path, O_RDONLY);
	line = get_next_line(fd);
	while(line && i < 6)
	{
		if (ft_strncmp(line, "NO", 2) == 0)
			cub->texture_north = correct_texture(line + 2, &i);
		if (ft_strncmp(line, "SO", 2) == 0)
			cub->texture_south = correct_texture(line + 2, &i);
		if (ft_strncmp(line, "EA", 2) == 0)
			cub->texture_east = correct_texture(line + 2, &i);
		if (ft_strncmp(line, "WE", 2) == 0)
			cub->texture_west = correct_texture(line + 2, &i);
		if (ft_strncmp(line, "F", 1) == 0)
			cub->floor = get_background(line + 1, &i);
		if (ft_strncmp(line, "C", 1) == 0)
			cub->ceiling = get_background(line + 1, &i);
		free(line);
		line = get_next_line(fd);
	}
	if (!cub->texture_east || !cub->texture_north || !cub->texture_south || !cub->texture_west || !cub->ceiling || !cub->floor)
		return (free(line), 0);
	free(line);
	return (fd);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
}

int	add_map(t_cub_data *cub)
{
	char	**split;
	char	*line;
	int		fd;
	int		i;
	char	*tmp;

	i = 0;
	split = malloc(sizeof(char *) * 1024);
	if (!split)
		return (0);
	fd = open(cub->map_path, O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!ft_strchr("NSWEFC", line[0]))
		{
			split[i] = ft_strdup(line);
			free(line);
			line = get_next_line(fd);
			i++;
		}
		else
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	split[i] = NULL;
	free(line);
	i = 0;
	while(split[i])
	{
		tmp = ft_strchr(split[i], '\n');
		if (tmp)
			*tmp = '\0';
		cub->map[i] = ft_strdup(split[i]);
		// printf("%s", cub->map[i]); //TODO remove
		i++;
	}
	cub->map[i] = NULL;
	free_split(split);
	return (1);
} //TODO shorten, maek betta, cheek mor possibilities

int	set_player(t_cub_data *cub, char c)
{
	if (c == 'N')
	{
		cub->player_direction_x = 0;
		cub->player_direction_y = -1;
		cub->player_plane_x = 0;
		cub->player_plane_y = 0.66;
	}
	if (c == 'S')
	{
		cub->player_direction_x = 0;
		cub->player_direction_y = 1;
		cub->player_plane_x = 0;
		cub->player_plane_y = -0.66;
	}
	if (c == 'E')
	{
		cub->player_direction_x = 1;
		cub->player_direction_y = 0;
		cub->player_plane_x = 0.66;
		cub->player_plane_y = 0;
	}
	if (c == 'W')
	{
		cub->player_direction_x = -1;
		cub->player_direction_y = 0;
		cub->player_plane_x = -0.66;
		cub->player_plane_y = 0;
	}
	return (1);
}

int	add_player(t_cub_data *cub)
{
	int		x;
	int		y;
	int		player_count;
	char	c;

	x = 0;
	y = 0;
	player_count = 0;
	c = '\0';
	while(cub->map[y])
	{
		if ((int)ft_strlen(cub->map[y]) > cub->map_width)
			cub->map_width = (int)ft_strlen(cub->map[y]);
		while(cub->map[y][x])
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S' || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
			{
				player_count++;
				cub->player_x = (double)x;
				cub->player_y = (double)y;
				c = cub->map[y][x];
			}
			x++;
		}
		x = 0;
		cub->map_height++;
		y++;
	}
	if (player_count != 1)
		return (0);
	set_player(cub, c);
	return (1);
}
