/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:38:51 by ldick             #+#    #+#             */
/*   Updated: 2025/04/30 09:09:29 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub_data *cub)
{
    // Set the player's starting position (example: map coordinates 13, 3)
	cub->p->x = 13.0; // Player's x position
	cub->p->y = 3.0;  // Player's y position
    // Set the player's initial direction (example: facing north)
    cub->p->dir_x = 0;
    cub->p->dir_y = -1;
    // Set the camera plane (perpendicular to the direction vector)
	cub->p->plane_x = 0.66; // Adjust for FOV (field of view)
	cub->p->plane_y = 0;
	// Debugging output to verify initialization
	printf("Player initialized:\n");
	printf("Position: (%f, %f)\n", cub->p->x, cub->p->y);
	printf("Direction: (%f, %f)\n", cub->p->dir_x, cub->p->dir_y);
	printf("Camera plane: (%f, %f)\n", cub->p->plane_x, cub->p->plane_y);
}

int	init(char *argv[], t_cub_data *cub)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	cub->p = safe_malloc(sizeof(t_player_data), cub, __func__);
	cub->texture = safe_malloc(sizeof(t_texture_data), cub, __func__);
	cub->texture->ceiling = safe_malloc(sizeof(t_ceiling_data), cub, __func__);
	cub->texture->floor = safe_malloc(sizeof(t_floor_data), cub, __func__);
	cub->minimap = safe_malloc(sizeof(t_minimap), cub, __func__);
	cub->text = safe_malloc(sizeof(t_textbox), cub, __func__);
	cub->move = safe_malloc(sizeof(t_move_data), cub, __func__);
	cub->minimap->size_x = 0;
	cub->minimap->size_y = 0;
	cub->mlx = mlx_init(WIDHT, HEIGHT, "cub3d", false);
	if (!cub->mlx)
	{
		return (ft_error(cub, "Failed to initialize mlx"), EXIT_FAILURE);
	}
	init_player(cub);
	mlx_set_setting(MLX_MAXIMIZED, true);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(cub, "Failed to open the .cub file"), 1);
	line = get_next_line(fd);
	cub->map_x = 0;
	cub->map_y = 0;
	while (i < 6)
	{
		i = add_texture(i, cub->texture, rm_s(line));
		if (i == 720)
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	init_map(cub, fd);
	init_color(cub->texture);
	init_texture(cub);
	cub->minimap->flag = true;
	return (0);
}
