/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:45:43 by ldick             #+#    #+#             */
/*   Updated: 2025/06/02 14:33:32 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leaks(void)
{
	system("leaks cub3D");
}

void	freeall(t_cub_data *cub)
{
	free_texture(cub);
	if (cub->img && cub->mlx)
		mlx_delete_image(cub->mlx, cub->img);
	if (cub->omg && cub->mlx)
		mlx_delete_image(cub->mlx, cub->omg);
	mlx_terminate(cub->mlx);
	free(cub);
}

int	main(int argc, char *argv[])
{
	t_cub_data	*cub;

	atexit(leaks);
	if (argc != 2)
		return (printf("Wrong number of Arguments\n"), 1);
	cub = malloc(sizeof(t_cub_data));
	if (!init(argv, cub))
		return (printf("Error\ninitialization failed\n"), freeall(cub), 0);
	if (!parsing(cub))
		return (printf("Error\nparsing failed\n"), freeall(cub), 0);
	if (!validate(cub))
		return (printf("Error\nvalidation failed\n"), freeall(cub),
			free_split(cub->map), 0);
	game(cub);
}
