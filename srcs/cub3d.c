/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:36:02 by ldick             #+#    #+#             */
/*   Updated: 2025/02/20 09:54:25 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	print_2(t_cub_data *cub)
// {
// 	int	i;

// 	i = 0;
// 	if (cub->texture->no)
// 		printf("%s\n", cub->texture->no);
// 	if (cub->texture->so)
// 		printf("%s\n", cub->texture->so);
// 	if (cub->texture->we)
// 		printf("%s\n", cub->texture->we);
// 	if (cub->texture->ea)
// 		printf("%s\n", cub->texture->ea);
// 	if (cub->texture->ceiling->ceiling)
// 		printf("%s\n", cub->texture->ceiling->ceiling);
// 	if (cub->texture->ceiling->r)
// 		printf("r--%d\n", cub->texture->ceiling->r);
// 	if (cub->texture->ceiling->g)
// 		printf("g--%d\n", cub->texture->ceiling->g);
// 	if (cub->texture->ceiling->b)
// 		printf("b--%d\n", cub->texture->ceiling->b);
// 	if (cub->texture->floor->floor)
// 		printf("%s\n", cub->texture->floor->floor);
// 	if (cub->texture->floor->r)
// 		printf("r--%d\n", cub->texture->floor->r);
// 	if (cub->texture->floor->g)
// 		printf("g--%d\n", cub->texture->floor->g);
// 	if (cub->texture->floor->b)
// 		printf("b--%d\n", cub->texture->floor->b);
// 	while (cub->map[i])
// 	{
// 		printf("%s\n", cub->map[i]);
// 		i++;
// 	}
// }

int	main(int argc, char *argv[])
{
	t_cub_data	*cub;

	cub = malloc(sizeof(t_cub_data));
	if (!cub)
		return (printf("Malloc error: cub\n"), EXIT_FAILURE);
	if (argc != 2)
		return (free(cub), printf("Wrogn number of Arguments\n"), 1);
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
