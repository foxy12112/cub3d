/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:40:54 by petrasostar       #+#    #+#             */
/*   Updated: 2025/04/10 09:56:34 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_texture(t_cub_data *cub)
{
	if (!cub->texture->ea || !cub->texture->no || !cub->texture->so
		|| !cub->texture->we
		|| !cub->texture->ceiling || !cub->texture->ceiling->ceiling
		|| !cub->texture->floor || !cub->texture->floor->floor)
	{
		ft_error(cub, "Error: Missing texture data.");
		return (EXIT_FAILURE);
	}
	cub->texture->ea_tex = create_image(cub, cub->texture->ea);
	cub->texture->no_tex = create_image(cub, cub->texture->no);
	cub->texture->so_tex = create_image(cub, cub->texture->so);
	cub->texture->we_tex = create_image(cub, cub->texture->we);
	return (0);
}

int	add_texture(int i, t_texture_data *texture, char *line)
{
	if (!line || *line == '\0')
		return (i);
	line = rm_s(line);
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		texture->no = ft_strdup(rm_s(line + 2));
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		texture->so = ft_strdup(rm_s(line + 2));
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		texture->we = ft_strdup(rm_s(line + 2));
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		texture->ea = ft_strdup(rm_s(line + 2));
	}
	else if (ft_strncmp(line, "F", 1) == 0)
		texture->floor->floor = ft_strdup(rm_s(line + 1));
	else if (ft_strncmp(line, "C", 1) == 0)
		texture->ceiling->ceiling = ft_strdup(rm_s(line + 1));
	else
		return (720);
	return (i + 1);
}

int	init_map(t_cub_data *cub, int fd)
{
	char	*newline;
	int		i;
	char	*line;

	cub->minimap = safe_malloc(sizeof(t_minimap), cub, __func__);
	cub->minimap->size_x = 0;
	cub->minimap->size_y = 0;
	line = get_next_line(fd);
	i = 0;
	cub->map = safe_malloc(sizeof(char *) * 1024, cub, __func__);
	cub->map_height = 0;
	cub->map_width = 0;
	while (line)
	{
		if ((int)ft_strlen(line) > cub->map_width)
			cub->map_width = (int)ft_strlen(line);
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		cub->map[i++] = ft_strdup(line);
		free(line);
		cub->map_height++;
		line = get_next_line(fd);
	}
	cub->map[i] = NULL;
	printf("Map dimensions: height = %d, width = %d\n", \
	cub->map_height, cub->map_width);
	return (EXIT_SUCCESS);
}

int	init_color(t_texture_data *texture)
{
	char	**tmp;

	tmp = ft_split(texture->ceiling->ceiling, ',');
	texture->ceiling->r = ft_atoi(tmp[0]);
	texture->ceiling->g = ft_atoi(tmp[1]);
	texture->ceiling->b = ft_atoi(tmp[2]);
	ft_memset(tmp, 0, sizeof(tmp));
	tmp = ft_split(texture->floor->floor, ',');
	texture->floor->r = ft_atoi(tmp[0]);
	texture->floor->g = ft_atoi(tmp[1]);
	texture->floor->b = ft_atoi(tmp[2]);
	free(tmp);
	tmp = NULL ;
	return (1);
}
