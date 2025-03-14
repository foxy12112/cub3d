/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:40:54 by petrasostar       #+#    #+#             */
/*   Updated: 2025/03/14 13:29:38 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init(char *argv[], t_cub_data *cub)
{
	int fd;
	char *line;
	int i;

	i = 0;
	// Security allocation for required data
	cub->p = safe_malloc(sizeof(t_player_data), cub, __func__);
	cub->texture = safe_malloc(sizeof(t_texture_data), cub, __func__);
	cub->texture->ceiling = safe_malloc(sizeof(t_ceiling_data), cub, __func__);
	cub->texture->floor = safe_malloc(sizeof(t_floor_data), cub, __func__);
	cub->minimap = safe_malloc(sizeof(t_minimap), cub, __func__);
	cub->text = safe_malloc(sizeof(t_textbox), cub, __func__);

	cub->minimap->size_x = 0;
	cub->minimap->size_y = 0;

	// Set up MLX to render
	mlx_set_setting(MLX_MAXIMIZED, true);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(cub, "Failed to open the .cub file"), 1);

	// Load lines from file
	line = get_next_line(fd);
	while (i < 6) { // Here we will load 6 key parameters (textures, colors)
		i = add_texture(i, cub->texture, rm_s(line));
		if (i == 720)  // If there was an error loading textures
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}

	// Initialize map and colors
	init_map(cub, fd);
	init_color(cub->texture);  // Initialization of colors (ceiling and floor)
	init_texture(cub);  // Texture initialization

	return 0;
}

int add_texture(int i, t_texture_data *texture, char *line)
{
    if (ft_strncmp(line, "NO", 2) == 0)
        texture->no = ft_strdup(line + 2);
    else if (ft_strncmp(line, "SO", 2) == 0)
        texture->so = ft_strdup(line + 2);
    else if (ft_strncmp(line, "WE", 2) == 0)
        texture->we = ft_strdup(line + 2);
    else if (ft_strncmp(line, "EA", 2) == 0)
        texture->ea = ft_strdup(line + 2);
    else if (ft_strncmp(line, "F", 1) == 0)
        texture->floor->floor = ft_strdup(line + 1);
    else if (ft_strncmp(line, "C", 1) == 0)
        texture->ceiling->ceiling = ft_strdup(line + 1);
    else if ((line)[0] == '\n')
        return (i);
    else
        return (720);
    return (i + 1);
}

int init_map(t_cub_data *cub, int fd)
{
    char *newline;
    int i;
    char *line;

    line = get_next_line(fd);
    i = 0;
    cub->map = safe_malloc(sizeof(char *) * 1024, cub, __func__);
    while (line) {
        if ((int)ft_strlen(line) > cub->minimap->size_x)
            cub->minimap->size_x = (int)ft_strlen(line);
        newline = ft_strchr(line, '\n');
        if (newline)
            *newline = '\0';
        cub->map[i++] = ft_strdup(line);
        free(line);
        line = get_next_line(fd);
        cub->minimap->size_y++;
    }
    cub->map[i] = NULL;
    return (EXIT_SUCCESS);
}

int init_color(t_texture_data *texture)
{
    char **tmp;

    tmp = ft_split(texture->ceiling->ceiling, ',');
    texture->ceiling->r = ft_atoi(tmp[0]);
    texture->ceiling->g = ft_atoi(tmp[1]);
    texture->ceiling->b = ft_atoi(tmp[2]);
    ft_memset(tmp, 0, sizeof(tmp));
    tmp = ft_split(texture->floor->floor, ',');
    texture->floor->r = ft_atoi(tmp[0]);
    texture->floor->g = ft_atoi(tmp[1]);
    texture->floor->b = ft_atoi(tmp[2]);
    return (free(tmp), 1);
}
