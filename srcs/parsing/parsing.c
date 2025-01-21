/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:55:37 by ldick             #+#    #+#             */
/*   Updated: 2025/01/20 19:14:28 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(char *argv[], t_cub_data *cub)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (i < 4)
	{
		if (ft_strncmp(line, "NO", 2) == 0)
		{
			cub->texture->no = ft_strdup(line + 2);
			i++;
		}
		if (ft_strncmp(line, "SO", 2) == 0)
		{
			cub->texture->so = ft_strdup(line + 2);
			i++;
		}
		if (ft_strncmp(line, "WE", 2) == 0)
		{
			cub->texture->we = ft_strdup(line + 2);
			i++;
		}
		if (ft_strncmp(line, "EA", 2) == 0)
		{
			cub->texture->ea = ft_strdup(line + 2);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("no %s\n", cub->texture->no);
	printf("so %s\n", cub->texture->so);
	printf("we %s\n", cub->texture->we);
	printf("ea %s\n", cub->texture->ea);
	return (1);
}
