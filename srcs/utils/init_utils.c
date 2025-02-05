/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:16:37 by ldick             #+#    #+#             */
/*   Updated: 2025/02/05 19:03:47 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*rm_s(char *str)
{
	int		i;
	int		j;
	int		lenght;

	lenght = ft_strlen(str);
	i = 0;
	j = 0;
	while (i < lenght)
	{
		if (str[i] != ' ')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

int	add_texture(int i, t_texture_data *texture, char *line)
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

int	init_map(t_cub_data *cub, int fd)
{
	char	*newline;
	int		i;
	char	*line;

	line = get_next_line(fd);
	i = 0;
	cub->map = safe_malloc(sizeof (char *) * 1024, cub, __func__);
	while (line)
	{
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		cub->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	cub->map[i] = NULL;
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
	return (free(tmp), 1);
}

void	malloc_all(t_cub_data *cub)
{
	cub->map = safe_malloc(1, cub, __func__);
	cub->texture->ceiling->ceiling = safe_malloc(1, cub, __func__);
	cub->texture->floor->floor = safe_malloc(1, cub, __func__);
	cub->texture->ea = safe_malloc(1, cub, __func__);
	cub->texture->we = safe_malloc(1, cub, __func__);
	cub->texture->no = safe_malloc(1, cub, __func__);
	cub->texture->so = safe_malloc(1, cub, __func__);
}
