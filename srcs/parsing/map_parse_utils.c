/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:34:40 by petrasostar       #+#    #+#             */
/*   Updated: 2025/04/24 09:43:59 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top(t_cub_data *cub)
{
	int	i;

	i = 0;
	while (cub->map[0][i] && (cub->map[0][i] == ' ' || cub->map[0][i] == '\t'))
		i++;
	while (cub->map[0][i])
	{
		if (cub->map[0][i] != '1' && cub->map[0][i] != ' ')
			return (ft_error(cub, "top not closed"), 1);
		i++;
	}
	i--;
	while (i >= 0 && (cub->map[0][i] == ' ' || cub->map[0][i] == '\t'))
		i--;
	if (cub->map[0][i] != '1')
		return (ft_error(cub, "top not closed"), 1);
	return (0);
}

int	check_bottom(t_cub_data *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!cub->map || !cub->map[y])
		return (ft_error(cub, "Map is empty or not properly initialized"), 1);
	while (cub->map[y] != NULL)
		y++;
	y--;
	while (y >= 0 && strlen(cub->map[y]) == 0)
		y--;
	if (y < 0)
		return (ft_error(cub, "No valid map data"), 1);
	int row_length = strlen(cub->map[y]);
	if (row_length == 0)
		return (ft_error(cub, "Last row is empty"), 1);
	while (x < row_length && (cub->map[y][x] == ' ' || cub->map[y][x] == '\t'))
		x++;
	while (x < row_length && cub->map[y][x])
	{
		if (cub->map[y][x] != '1' && cub->map[y][x] != ' ')
			return (ft_error(cub, "bottom not closed"), 1);
		x++;
	}
	x--;
	while (x >= 0 && (cub->map[y][x] == ' ' || cub->map[y][x] == '\t'))
		x--;
	if (x >= 0 && cub->map[y][x] != '1')
		return (ft_error(cub, "bottom not closed"), 1);
	return (0);
}

int	check_sides(t_cub_data *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x] == ' ' || cub->map[y][x] == '\t')
			x++;
		if (cub->map[y][x] != '1' && cub->map[y][x] != '\0')
			return (ft_error(cub, "sides not closed"), 1);
		x = ft_strlen(cub->map[y]) - 1;
		while (cub->map[y][x] == ' ' || cub->map[y][x] == '\t')
			x--;
		if (cub->map[y][x] != '1')
			return (ft_error(cub, "sides not closed"), 1);
		if (cub->map[y][x + 1] == '\0')
			break ;
		y++;
	}
	return (0);
}

int	check_map_validity(t_cub_data *cub)
{
	if (!cub || !cub->map)
	{
		return (ft_error(cub, "Invalid map data"), FAILURE);
	}
	if (cub->map_height < 3 || cub->map_width < 3)
	{
		return (ft_error(cub, "Map is too small"), FAILURE);
	}
	if (check_invalid_chars(cub) == FAILURE)
	{
		return (ft_error(cub, "Map elements are invalid"), FAILURE);
	}
	return (SUCCESS);
}
