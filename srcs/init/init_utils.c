/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:47:47 by ldick             #+#    #+#             */
/*   Updated: 2025/06/03 15:29:41 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *path)
{
	int	lenght;

	lenght = ft_strlen(path);
	if (path[lenght - 1] != 'b' || path[lenght - 2] != 'u' || path[lenght
			- 3] != 'c' || path[lenght - 4] != '.')
		return (0);
	return (1);
}

int	set_player(t_cub_data *cub, char c, int x, int y)
{
	if (c == 'N')
	{
		cub->player_direction_y = -1;
		cub->player_plane_y = 1;
	}
	if (c == 'S')
	{
		cub->player_direction_y = 1;
		cub->player_plane_y = -1;
	}
	if (c == 'E')
	{
		cub->player_direction_x = 1;
		cub->player_plane_x = 1;
	}
	if (c == 'W')
	{
		cub->player_direction_x = -1;
		cub->player_plane_x = -1;
	}
	cub->player_x = (double)x + 0.5;
	cub->player_y = (double)y + 0.5;
	cub->player_start_x = (double)x + 0.5;
	cub->player_start_y = (double)y + 0.5;
	return (1);
}

int	check_color(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	get_background(char *line)
{
	char	**tmp;
	int		color;

	tmp = ft_split(rm_s(line), ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
		return (0);
	if (!check_color(tmp[0]) || !check_color(tmp[1]) || !check_color(tmp[2]))
	{
		free(tmp[0]);
		free(tmp[1]);
		free(tmp[2]);
		free(tmp);
		return (0);
	}
	color = get_color(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]), 255);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	if (!color)
		return (0);
	return (color);
	return (0);
}
