/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:08:22 by ldick             #+#    #+#             */
/*   Updated: 2025/05/31 16:56:06 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_background(char *line, int *i)
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
	while (line && i < 6)
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
	return (close(fd), free(line), 1);
}

int	add_map(t_cub_data *cub)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(cub->map_path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!ft_strchr("NSWEFC", line[0]))
		{
			cub->map[i] = ft_strdup(line);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	cub->map[i] = NULL;
	return (free(line), 1);
}

int	set_player(t_cub_data *cub, char c, int x, int y)
{
	if (c == 'N')
	{
		cub->player_direction_y = -1;
		cub->player_plane_y = 0.66;
	}
	if (c == 'S')
	{
		cub->player_direction_y = 1;
		cub->player_plane_y = -0.66;
	}
	if (c == 'E')
	{
		cub->player_direction_x = 1;
		cub->player_plane_x = 0.66;
	}
	if (c == 'W')
	{
		cub->player_direction_x = -1;
		cub->player_plane_x = -0.66;
	}
	cub->player_x = (double)x;
	cub->player_y = (double)y;
	cub->player_start_x = (double)x;
	cub->player_start_y = (double)y;
	return (1);
}

int	add_player(t_cub_data *cub)
{
	int		x;
	int		y;
	int		player_count;

	y = 0;
	player_count = 0;
	while (cub->map[++y])
	{
		if ((int)ft_strlen(cub->map[y]) > cub->map_width)
			cub->map_width = (int)ft_strlen(cub->map[y]);
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
				|| cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
			{
				player_count++;
				set_player(cub, cub->map[y][x], x, y);
			}
		}
		cub->map_height++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}
