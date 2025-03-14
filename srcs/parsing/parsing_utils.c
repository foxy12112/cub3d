/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:11:53 by ldick             #+#    #+#             */
/*   Updated: 2025/03/10 11:17:08 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void printMap(t_cub_data *cub) 
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
		return ;
	cub->p->dir = (c == 'N') ? NORTH : (c == 'S') ? SOUTH : (c == 'E') ? EAST : WEST;
	cub->p->x = (double)cub->p->start_x;
	cub->p->y = (double)cub->p->start_y;
    i = 0;
    if (cub->map == NULL) {
        printf("Error: Map is NULL\n");
        return;
    }

    i = 0;
    while (cub->map[i] != NULL) {
        printf("%s\n", cub->map[i]);
        i++;
    }
}

int check_leaks(char **map, t_cub_data *cub)
{
	size_t x;
    size_t y;

    x = 0;
    y = 0;
    while (map[y])
    {
        while (map[y][x])
        {
            if (map[y][x] == '0')
            {
                if ((y == 0 || !map[y - 1]) || ((y + 1) == (size_t)cub->map_height || !map[y + 1]) ||
                    (x == 0 || !map[y][x - 1]) || (x + 1 == (size_t)ft_strlen(map[y]) || !map[y][x + 1]))
                {
                    return (ft_error(cub, "overhang not closed"), 1);
                }
            }
            x++;
        }
        y++;
        x = 0;
    }
    return (0);
}

int check_map_dim(t_cub_data *cub)
{
    if (cub->map_height < 3 || cub->map_width < 3)
    {
        ft_error(cub, "Map is too small, must be at least 3x3");
        return 1;
    }
    return 0;
}

void free_double_array(char **array)
{
    int i = 0;

    if (array)
    {
        while (array[i] != NULL)
        {
            free(array[i]);
            i++;
        }
        free(array);
    }
}