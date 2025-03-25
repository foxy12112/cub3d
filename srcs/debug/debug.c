/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:58:57 by psostari          #+#    #+#             */
/*   Updated: 2025/03/19 12:08:29 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map_lines(char **map)
{
	int	i;

	printf("\n");
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("\n");
}

/* printing info about minimap during game execution,
helps detect size, map, scaling problems
for minimp render
*/
void	print_minimap_data(t_minimap *minimap)
{
	printf("\n==== MINIMAP====\n");
	printf("Minimap scale: %f\n", minimap->scale);
	printf("Minimap size_x: %d\n", minimap->size_x);
	printf("Minimap size_y: %d\n", minimap->size_y);
	printf("Minimap scale_x: %f\n", minimap->scale_x);
	printf("Minimap scale_y: %f\n", minimap->scale_y);
	if (minimap->img)
	{
		printf("Minimap image exists\n");
	}
	else
	{
		printf("Minimap image is not set\n");
	}
	if (minimap->p_img)
	{
		printf("Minimap player image exists\n");
	}
	else
	{
		printf("Minimap player image is not set\n");
	}
}

void	print_mapinfo(t_cub_data *data)
{
	printf("\n==== MAP ====\n");
	printf("Map height: %d\n", data->map_height);
	printf("Map width: %d\n", data->map_width);
	print_map_lines(data->map);
	printf("\n---- TEXTURES & COLORS ----\n");
	printf("Color ceiling: #%x\n", data->texture->ceiling->r << 16 \
		| data->texture->ceiling->g << 8 | data->texture->ceiling->b);
	printf("Color floor: #%x\n", data->texture->floor->r << 16 \
		| data->texture->floor->g << 8 | data->texture->floor->b);
	printf("Texture north: %s\n", data->texture->no);
	printf("Texture south: %s\n", data->texture->so);
	printf("Texture east: %s\n", data->texture->ea);
	printf("Texture west: %s\n", data->texture->we);
}

void	print_player_info(t_cub_data *data)
{
	printf("\n==== PLAYER ====\n");
	printf("Player pos: ");
	printf("x = %f, y = %f\n", data->p->x, data->p->y);
	printf("Player direction: %c ", (char)(data->p->dir));
	printf("(x = %f, y = %f)\n", data->p->dir_x, data->p->dir_y);
}
/*
function is used to print out information about the
current state of the game to the console:
map, info, texture, color, directions, players position
and orientation
*/

void	display_data(t_cub_data *data)
{
	print_mapinfo(data);
	print_player_info(data);
	printf("\n");
}

/* display data
==== MAP ====
Map height: 10
Map width: 10
##########
#........#
#........#
#........#
#..P.....#
#........#
#........#
#........#
#........#
#........#
##########

---- TEXTURES & COLORS ----
Color ceiling: #ff6600
Color floor: #003366
Texture north: textures/north_texture.png
Texture south: textures/south_texture.png
Texture east: textures/east_texture.png
Texture west: textures/west_texture.png

==== PLAYER ====
Player pos:
x = 5.000000, y = 4.000000
Player direction: N (x = 0.000000, y = -1.000000)

*/

/*
gcc -g -DDEBUG -I includes -I main-libs srcs/debug/debug.c -o bin/debug.debug

*/
