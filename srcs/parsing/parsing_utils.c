/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:11:53 by ldick             #+#    #+#             */
/*   Updated: 2025/05/17 17:51:58 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_player(t_cub_data *cub)
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
		cub->p->plane_x = 0;
		cub->p->plane_y = 0.66;
	}
	else if (c == 'S')
	{
		cub->p->dir_x = 0;
		cub->p->dir_y = 1;
		cub->p->plane_x = 0;
		cub->p->plane_y = -0.66;
	}
	else if (c == 'E')
	{
		cub->p->dir_x = 1;
		cub->p->dir_y = 0;
		cub->p->plane_x = 0.66;
		cub->p->plane_y = 0;
	}
	else if (c == 'W')
	{
		cub->p->dir_x = -1;
		cub->p->dir_y = 0;
		cub->p->plane_x = -0.66;
		cub->p->plane_y = 0;
	}
	cub->p->dir = atan2(cub->p->dir_x, cub->p->dir_y);
	cub->map_y = cub->p->start_x;
	cub->map_x = cub->p->start_y;
	cub->p->x = (double)cub->p->start_x * 22 + 55;
	cub->p->y = (double)cub->p->start_y * 22 + 55;
	return (0);
}

int	check_textures(t_cub_data *cub)
{
	// if (open(cub->texture->no, O_RDONLY) == -1)
	// 	return (1);
	(void)cub;
	return (0);
}

int	is_closed(t_cub_data *cub)
{
	check_top(cub);
	check_bottom(cub);
	check_sides(cub);
	check_leaks(cub->map, cub);
	printf("map is closed :)\n");
	return (0);
}

int	check_map(t_cub_data *cub)
{
	if (check_player(cub) == 1)
		ft_error(cub, "muultiple or no player positions");
	if (is_closed(cub) == 1)
		ft_error(cub, "error: map not closed");
	return (0);
}
