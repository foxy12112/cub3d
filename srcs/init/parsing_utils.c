/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:08:22 by ldick             #+#    #+#             */
/*   Updated: 2025/06/03 15:25:29 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	counter(t_cub_data *cub, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		cub->counter.north_texture++;
	if (ft_strncmp(line, "SO", 2) == 0)
		cub->counter.south_texture++;
	if (ft_strncmp(line, "EA", 2) == 0)
		cub->counter.east_texture++;
	if (ft_strncmp(line, "WE", 2) == 0)
		cub->counter.west_texture++;
	if (ft_strncmp(line, "F", 1) == 0)
		cub->counter.floor++;
	if (ft_strncmp(line, "C", 1) == 0)
		cub->counter.ceiling++;
}

int	validate_counter(t_cub_data *cub)
{
	if (cub->counter.floor != 1)
		return (0);
	if (cub->counter.ceiling != 1)
		return (0);
	if (cub->counter.west_texture != 1)
		return (0);
	if (cub->counter.east_texture != 1)
		return (0);
	if (cub->counter.south_texture != 1)
		return (0);
	if (cub->counter.north_texture != 1)
		return (0);
	return (1);
}

int	add_textures(t_cub_data *cub)
{
	int		fd;
	char	*line;

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
		if (ft_strchr("NSWE", rm_s(line)[0]) && (!check_png(rm_s(line + 2))
			|| !check_image(line + 2)))
			return (free(line), printf(PNG), 0);
		if (add_textures_utils(cub, line) == 0)
			break ;
		counter(cub, line);
		if (ft_strchr(" 01", line[0]))
			return (free(line), printf(INVALID_DATA), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), free(line), validate_counter(cub));
}

int	add_map(t_cub_data *cub)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(cub->map_path, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nfailed to open map"), 0);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strchr("NSWEFC\n", line[0]))
			cub->map[i++] = ft_strdup(line);
		if (line[0] == '\n' && i > 0)
		{
			free(line);
			return (close(fd), printf("Error\nempty line in map\n"), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	cub->map[i] = NULL;
	return (close(fd), 1);
}

int	add_player(t_cub_data *cub)
{
	int	x;
	int	y;
	int	player_count;

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
