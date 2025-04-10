/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:38:51 by ldick             #+#    #+#             */
/*   Updated: 2025/04/10 09:58:30 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	cub->minimap->size_x = 0;
	cub->minimap->size_y = 0;
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!cub->mlx)
	{
		return (ft_error(cub, "Failed to initialize mlx"), EXIT_FAILURE);
	}
	mlx_set_setting(MLX_MAXIMIZED, true);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(cub, "Failed to open the .cub file"), 1);
	line = get_next_line(fd);
	while (i < 6)
	{
		i = add_texture(i, cub->texture, rm_s(line));
		if (i == 720)
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	init_map(cub, fd);
	init_color(cub->texture);
	init_texture(cub);
	cub->minimap->flag = true;
	return (0);
}
