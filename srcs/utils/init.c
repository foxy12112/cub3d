/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foxy <foxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:38:51 by ldick             #+#    #+#             */
/*   Updated: 2025/01/23 19:21:36 by foxy             ###   ########.fr       */
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

int	init(char *argv[], t_cub_data *cub)
{
	cub->texture = safe_malloc(sizeof(t_texture_data), cub, __func__);
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (i < 6)
	{
		i = add_texture(i, cub->texture, rm_s(line));
		if (i == 720)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("no %s\n", cub->texture->no);
	printf("so %s\n", cub->texture->so);
	printf("we %s\n", cub->texture->we);
	printf("ea %s\n", cub->texture->ea);
	printf("Floor %s\n", cub->texture->floor);
	printf("Ceiling %s\n", cub->texture->ceiling);

	return (1);
}
