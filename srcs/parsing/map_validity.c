/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:55:55 by petrasostar       #+#    #+#             */
/*   Updated: 2025/04/24 10:35:01 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_exists(t_cub_data *cub)
{
	if (!cub || !cub->map || !cub->map[0])
		return (ft_error(cub, "Map data is invalid"), 1);
	return (0);
}

int	check_player(t_cub_data *cub)
{
	int		i;
	int		j;
	int		player_count;
	char	c;

	c = '\0';
	player_count = 0;
	i = 0;
	j = 0;
	while (cub->map[i])
	{
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
			{
				player_count++;
				cub->p->start_x = j;
				cub->p->start_y = i;
				c = cub->map[i][j];
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (player_count != 1)
		return (1);
	if (c == 'N')
	{
		cub->p->dir_x = 0;
		cub->p->dir_y = -1;
	}
	else if (c == 'S')
	{
		cub->p->dir_x = 0;
		cub->p->dir_y = 1;
	}
	else if (c == 'E')
	{
		cub->p->dir_x = 1;
		cub->p->dir_y = 0;
	}
	else if (c == 'W')
	{
		cub->p->dir_x = -1;
		cub->p->dir_y = 0;
	}
	cub->p->dir = atan2(cub->p->dir_x, cub->p->dir_y);
	cub->p->x = (double)cub->p->start_x * 22 + 55;
	cub->p->y = (double)cub->p->start_y * 22 + 55;
	return (0);
}

int	is_closed(t_cub_data *cub)
{
	if (check_top(cub) == 1)
		return (ft_error(cub, "Map is not properly closed at the top"),
			FAILURE);
	if (check_bottom(cub) == 1)
		return (ft_error(cub, "Map is not properly closed at the bottom"),
			FAILURE);
	if (check_sides(cub) == 1)
		return (ft_error(cub, "Map is not properly closed on the sides"),
			FAILURE);
	if (check_leaks(cub->map, cub) == 1)
		return (ft_error(cub, "Map has leaks"), FAILURE);
	printf("Map is properly closed :)\n");
	return (0);
}

int	check_map(t_cub_data *cub)
{
	if (check_map_exists(cub) == 1)
		return (ft_error(cub, "Map does not exist"), FAILURE);
	if (check_player(cub) == 1)
		return (ft_error(cub, "Multiple or no player positions found"),
			FAILURE);
	if (is_closed(cub) == 1)
		return (ft_error(cub, "Error: Map is not properly closed"), FAILURE);
	return (0);
}
