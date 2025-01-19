/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:36:02 by ldick             #+#    #+#             */
/*   Updated: 2025/01/19 18:31:55 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub_data	*cub;

	(void)argc;
	cub = (t_cub_data *)malloc(sizeof(t_cub_data));
	cub->texture = (t_texture_data *)malloc(sizeof(t_texture_data));
	if (!cub)
		return (printf("Malloc error: cub\n"), EXIT_FAILURE);
	// if (initialize(argv, cub) == 1)
	// 	return (ft_error(), EXIT_FAILURE);
	// if (parsing(cub) == 1)
	// 	return (ft_error(), EXIT_FAILURE);
	// if (game_loop(cub) == 1)
	// 	return (ft_error(), EXIT_FAILURE);
	initialize(argv, cub);
	// clean_all(cub);
	return (0);
}
