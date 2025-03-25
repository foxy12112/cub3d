/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:34:40 by petrasostar       #+#    #+#             */
/*   Updated: 2025/03/19 12:20:23 by psostari         ###   ########.fr       */
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
	while (cub->map[y])
		y++;
	y--;
	while (cub->map[y][x] && (cub->map[y][x] == ' ' || cub->map[y][x] == '\t'))
		x++;
	while (cub->map[y][x])
	{
		if (cub->map[y][x] != '1' && cub->map[y][x] != ' ')
			return (ft_error(cub, "bottom not closed"), 1);
		x++;
	}
	x--;
	while (x >= 0 && (cub->map[y][x] == ' ' || cub->map[y][x] == '\t'))
		x--;
	if (cub->map[y][x] != '1')
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
		if (cub->map[y][x] != '1')
			return (ft_error(cub, "sides not closed"), 1);
		x = ft_strlen(cub->map[y]) - 1;
		while (cub->map[y][x] == ' ' || cub->map[y][x] == '\t')
			x--;
		if (cub->map[y][x] != '1')
			return (ft_error(cub, "sides not closed"), 1);
		y++;
	}
	return (0);
}

int	check_map_validity(t_cub_data *cub)
{
    //Check for NULL pointers (ensure that the map and other data exist)
	if (!cub || !cub->map)
	{
		return (ft_error(cub, "Invalid map data"), FAILURE);  // Return error if the map data is missing or invalid
	}
    //Check if the map has minimum dimensions (height and width)
	if (cub->map_height < 3 || cub->map_width < 3)
	{
		return (ft_error(cub, "Map is too small"), FAILURE); // Return error if the map is smaller than 3x3
	}
    //You can add other checks, such as verifying that the map contains the necessary elements (e.g., walls, player, etc.)
	if (check_invalid_chars(cub) == FAILURE)
	{
		return (ft_error(cub, "Map elements are invalid"), FAILURE);  //Return error if the map elements (like walls, empty spaces, etc.) are incorrect
	}
	return (SUCCESS); //Return success if all checks pass
}
