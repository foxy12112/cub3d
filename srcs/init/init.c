/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:00:34 by ldick             #+#    #+#             */
/*   Updated: 2025/06/03 14:27:55 by ldick            ###   ########.fr       */
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

void	init_data(t_cub_data *cub)
{
	cub->counter.floor = 0;
	cub->counter.ceiling = 0;
	cub->counter.east_texture = 0;
	cub->counter.west_texture = 0;
	cub->counter.south_texture = 0;
	cub->counter.north_texture = 0;
}

int	init(char **argv, t_cub_data *cub)
{
	cub->mlx = mlx_init(WIDHT, HEIGHT, "cub3D", false);
	if (!cub->mlx)
		return (0);
	if (!check_extension(argv[1]) || !check_file_existance(argv[1]))
	{
		printf("Error\nwrong file extension or file doesnt exist\n");
		mlx_terminate(cub->mlx);
		free(cub);
		exit(0);
	}
	cub->map_path = argv[1];
	cub->map = malloc(sizeof(char *) * 1024);
	if (!cub->map)
		return (0);
	ft_bzero(cub->map, 1024);
	cub->map_height = 0;
	cub->map_flag = 1;
	cub->map_width = 0;
	cub->player_direction_x = 0;
	cub->player_direction_y = 0;
	cub->player_plane_x = 0;
	cub->player_plane_y = 0;
	cub->mouse_on_off = false;
	init_data(cub);
	return (1);
}
