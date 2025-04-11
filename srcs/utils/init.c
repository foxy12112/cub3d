/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:38:51 by ldick             #+#    #+#             */
/*   Updated: 2025/04/09 11:28:39 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// int	initialize(char *argv[], t_cub_data *cub)
// {
// 	int		fd;
// 	char	*line;

// 	(void)cub;
// 	fd = open(argv[1], O_RDONLY);
// 	line = "0";
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (1);
// }

void	init_texture(t_cub_data *cub)
{
	cub->texture->ea[ft_strlen(cub->texture->ea) - 1] = '\0';
	cub->texture->no[ft_strlen(cub->texture->no) - 1] = '\0';
	cub->texture->so[ft_strlen(cub->texture->so) - 1] = '\0';
	cub->texture->we[ft_strlen(cub->texture->we) - 1] = '\0';
	cub->texture->ea_tex = create_image(cub, cub->texture->ea);
	cub->texture->no_tex = create_image(cub, cub->texture->no);
	cub->texture->so_tex = create_image(cub, cub->texture->so);
	cub->texture->we_tex = create_image(cub, cub->texture->we);
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
	cub->calculated = false;
	mlx_set_setting(MLX_MAXIMIZED, true);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	cub->time = 0;
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

