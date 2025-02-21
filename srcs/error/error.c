/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:50:58 by ldick             #+#    #+#             */
/*   Updated: 2025/02/21 09:52:22 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_cub_data *cub, char *error_msg)
{
	clean_all(cub);
	printf("%s\n", error_msg);
	exit(1);
}

void	clean_all(t_cub_data *cub)
{
	if (cub->texture->we)
		free(cub->texture->we);
	if (cub->texture->no)
		free(cub->texture->no);
	if (cub->texture->so)
		free(cub->texture->so);
	if (cub->texture->ea)
		free(cub->texture->ea);
	if (cub->texture->ceiling->ceiling)
		free(cub->texture->ceiling->ceiling);
	if (cub->texture->floor->floor)
		free(cub->texture->floor->floor);
}

