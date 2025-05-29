/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foxy <foxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:00:34 by ldick             #+#    #+#             */
/*   Updated: 2025/05/29 18:33:08 by foxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_existance(char *line)
{
	int	fd;

	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	init(char **argv, t_cub_data *cub)
{
	cub->mlx = mlx_init(WIDHT, HEIGHT, "cub3D", false);
	if (!cub->mlx)
		return (0);
	if (!check_extension(argv[1]))
		return (printf("Error\n"), free(cub->mlx), 0);
	if (!check_file_existance(argv[1]))
		return (printf("Error\n"), free(cub->mlx), 0);
	cub->map_path = argv[1];
	cub->map = malloc(sizeof(char *) * 1024);
	cub->map_height = 0;
	cub->map_width = 0;
	if (!cub->map)
		return (0);
	return (1);
}
