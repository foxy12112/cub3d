/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:35:29 by ldick             #+#    #+#             */
/*   Updated: 2025/03/14 17:54:15 by ldick            ###   ########.fr       */
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
// int	check_overhangs(t_cub_data *cub)
// {
// 	int	row1;
// 	int	row2;
// 	int	y;
// 	int	x;

// 	x =0 ;
// 	row1 = 0;
// 	row2 = 0;
// 	y = 0;
// 	while(cub->map[y])
// 	{
// // dprintf(2, "----------------------------------------------------------------------------------------------------------\n");
// 		if (row1 == 0)
// 		{
// 			row1 = ft_strlen(cub->map[y]);
// 			y++;
// 			row2 = ft_strlen(cub->map[y]);
// 		}
// 		if (row1 > row2)
// 		{
// 			x = row2;
// 			printf("%d--%d\n", y, x);
// 			while(cub->map[y][x])
// 			{
// 				if (x >= row1 || !cub->map[y][x])
// 					break ;
// 				if (cub->map[y][x] != '1' && cub->map[y][x] != ' ')
// 				{
// 					return (ft_error(cub, "map is not closed"), 1);
// 				}
// 				x++;
// 			}
// 		}
// // dprintf(2, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
// 		row1 = ft_strlen(cub->map[y]);
// 		y++;
// 		row2 = ft_strlen(cub->map[y]);
// 	}
// 	return (0);
// }

// void	floodfill(char **map, int x, int y)
// {

// 	if (map && y >= 0 && map[y] && x >= 0 && x <= (int)ft_strlen(map[y]) && map[y][x] && map[y][x] != '0' && map[y][x] != '*')
// 	{
// 		map[y][x] = '*';
// 		floodfill(map, x, y + 1);
// 		floodfill(map, x - 1, y);
// 		floodfill(map, x, y - 1);
// 		floodfill(map, x + 1, y);
// 	}
// }

int		check_leaks(char **map, t_cub_data *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while(map[y])
	{
		while(map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (!map[y - 1] || !map[y + 1] || !map[y - 1][x] || !map[y + 1][x])
					return (ft_error(cub, "overhang not closed"), false);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (true);
}

int	check_sides(t_cub_data *cub)
{
	int	y;

	y = 0;
	while (cub->map[y])
	{
		if ((cub->map[y][0] != ' ' && cub->map[y][0] != '1') || (cub->map[y][ft_strlen(cub->map[y]) - 1] != ' ' && cub->map[y][ft_strlen(cub->map[y]) - 1] != '1'))
			return (ft_error(cub, "sides not closed"), 1);
		y++;
	}
	return (0);
}

