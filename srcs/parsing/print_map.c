/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:11:53 by ldick             #+#    #+#             */
/*   Updated: 2025/03/19 11:40:26 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_map(t_cub_data *cub)
// {
// 	int	    i;
// 	int	    j;
// 	int	    player_count;
// 	char    c;

// 	c = '\0';
// 	player_count = 0;
// 	i = 0;
// 	j = 0;
// 	while (cub->map[i])
// 	{
// 		while (cub->map[i][j])
// 		{
// 			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' ||
// 				cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
// 			{
// 				player_count++;
// 				cub->p->start_x = j;
// 				cub->p->start_y = i;
// 				c = cub->map[i][j];
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	if (player_count != 1)
// 		return ;
// 	if (c == 'N')
// 		cub->p->dir = NORTH;
// 	else if (c == 'S')
// 		cub->p->dir = SOUTH;
// 	else if (c == 'E')
// 		cub->p->dir = EAST;
// 	else
// 		cub->p->dir = WEST;
// 	cub->p->x = (double)cub->p->start_x;
// 	cub->p->y = (double)cub->p->start_y;
// 	i = 0;
// 	if (cub->map == NULL)
// 	{
// 		printf("Error: Map is NULL\n");
// 		return ;
// 	}
// 	while (cub->map[i] != NULL)
// 	{
// 		printf("%s\n", cub->map[i]);
// 		i++;
// 	}
// }
void	set_player_direction(t_cub_data *cub, char c)
{
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
}

void	set_player_position(t_cub_data *cub, int j, int i, char c)
{
	cub->p->start_x = j;
	cub->p->start_y = i;
	cub->p->x = (double)cub->p->start_x;
	cub->p->y = (double)cub->p->start_y;
	set_player_direction(cub, c);
}

int	check_and_find_player(t_cub_data *cub)
{
	int		i;
	int		j;
	int		player_count;
	char	c;

	i = 0;
	j = 0;
	player_count = 0;
	c = '\0';
	while (cub->map[i])
	{
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' ||
				cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
			{
				player_count++;
				set_player_position(cub, j, i, cub->map[i][j]);
				c = cub->map[i][j];
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (player_count);
}

void	print_map(t_cub_data *cub)
{
	int		i;
	int		player_count;

	player_count = check_and_find_player(cub);
	if (player_count != 1)
		return ;
	i = 0;
	if (cub->map == NULL)
	{
		printf("Error: Map is NULL\n");
		return ;
	}
	while (cub->map[i] != NULL)
	{
		printf("%s\n", cub->map[i]);
		i++;
	}
}
