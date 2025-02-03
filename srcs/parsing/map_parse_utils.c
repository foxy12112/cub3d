/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:35:29 by ldick             #+#    #+#             */
/*   Updated: 2025/02/03 14:40:48 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top(t_cub_data *cub)
{
	int	i;

	i = 0;
	while (cub->map[0][i])
	{
		if (cub->map[0][i] != ' ' && cub->map[0][i] != '1')
			return (ft_error(cub, "top not closed"), 1);
		i++;
	}
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
	while (cub->map[y][x])
	{
		if (cub->map[y][x] != ' ' && cub->map[y][x] != '1')
			return (ft_error(cub, "bottom not closed"), 1);
		x++;
	}
	return (0);
}

void printMap(char **map) {
    for (int i = 0; map[i] != NULL; i++) { // Iterate until a NULL pointer is found
        printf("%s\n", map[i]); // Print each row (string)
    }
}

int	check_sides(t_cub_data *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 6;
	printMap(cub->map);
	while (cub->map[y])
	{
		if ((cub->map[y][0] != ' ' && cub->map[y][0] != '1')
			|| (cub->map[y][ft_strlen(cub->map[y]) - 1] != ' '
				&& cub->map[y][ft_strlen(cub->map[y]) - 1] != '1'))
			return (ft_error(cub, "sides not closed"), 1);
		y++;
	}
	return (0);
}
