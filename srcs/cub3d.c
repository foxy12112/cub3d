/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:45:43 by ldick             #+#    #+#             */
/*   Updated: 2025/05/30 16:48:04 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub_data	*cub;

	if (argc != 2)
		return (printf("Wrong number of Arguments\n"), 1);
	cub = malloc(sizeof(t_cub_data));
	if (!init(argv, cub))
		return (printf("Error\ninitialization failed\n"), 0);
	if (!parsing(cub))
		return (printf("Error\nparsing failed\n"), 0);
	if (!validate(cub))
		return (printf("Error\nvalidation failed\n"), 0);
	game(cub);
}
