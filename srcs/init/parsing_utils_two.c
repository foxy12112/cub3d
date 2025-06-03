/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:10:47 by ldick             #+#    #+#             */
/*   Updated: 2025/06/03 15:22:42 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_textures_utils(t_cub_data *cub, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		cub->texture_north = correct_texture(line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		cub->texture_south = correct_texture(line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		cub->texture_east = correct_texture(line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		cub->texture_west = correct_texture(line + 2);
	else if (ft_strncmp(line, "F", 1) == 0)
		cub->floor = get_background(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		cub->ceiling = get_background(line + 1);
	else
		return (0);
	return (1);
}

int	check_image(char *line)
{
	int	fd;

	fd = open(rm_s(line), O_RDONLY);
	if (fd < 0)
		return (0);
	return (close(fd), 1);
}
