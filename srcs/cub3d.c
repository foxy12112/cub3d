/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:36:02 by ldick             #+#    #+#             */
/*   Updated: 2025/03/18 19:14:23 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub_data	*cub;

	cub = malloc(sizeof(t_cub_data));
	if (!cub)
		return (printf("Malloc error: cub\n"), EXIT_FAILURE);
	if (argc != 2)
		return (free(cub), printf("Wrogn number of Arguments\n"), 1);
	cub->mlx = mlx_init(WIDHT, HEIGHT, "cub3d", false);
	if (init(argv, cub) == 1)
		return (ft_error(cub, "error in init"), EXIT_FAILURE);
	if (parsing(cub) == 1)
		return (ft_error(cub, "error in parsing"), EXIT_FAILURE);
	// print_2(cub);
	game_loop(cub);
	// if (game_loop(cub) == 1)
	// 	return (ft_error(), EXIT_FAILURE);
	// initialize(argv, cub);
	// clean_all(cub);
	return (0);
}


