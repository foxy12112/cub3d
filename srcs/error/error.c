/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:50:58 by ldick             #+#    #+#             */
/*   Updated: 2025/04/07 12:11:23 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_cub_data *cub, const char *error_msg)
{
	clean_all(cub);
	printf("%s\n", error_msg);
	exit(1);
}

// void	clean_all(t_cub_data *cub)
// {
// 	if (cub->texture->we)
// 		free(cub->texture->we);
// 	if (cub->texture->no)
// 		free(cub->texture->no);
// 	if (cub->texture->so)
// 		free(cub->texture->so);
// 	if (cub->texture->ea)
// 		free(cub->texture->ea);
// 	if (cub->texture->ceiling->ceiling)
// 		free(cub->texture->ceiling->ceiling);
// 	if (cub->texture->floor->floor)
// 		free(cub->texture->floor->floor);
// }

// void	clean_all(t_cub_data *cub)
// {
// 	if (cub && cub->texture)
// 	{
// 		if (cub->texture->we)
// 			free(cub->texture->we);
// 		if (cub->texture->no)
// 			free(cub->texture->no);
// 		if (cub->texture->so)
// 			free(cub->texture->so);
// 		if (cub->texture->ea)
// 			free(cub->texture->ea);
// 		if (cub->texture->ceiling && cub->texture->ceiling->ceiling)
// 			free(cub->texture->ceiling->ceiling);
// 		if (cub->texture->floor && cub->texture->floor->floor)
// 			free(cub->texture->floor->floor);
// 	}
// }

void clean_all(t_cub_data *cub)
{
    if (cub->texture)
    {
        free(cub->texture->ea);
        free(cub->texture->no);
        free(cub->texture->so);
        free(cub->texture->we);
        free(cub->texture->ceiling->ceiling);
        free(cub->texture->floor->floor);
        free(cub->texture);
        cub->texture = NULL; // Set to NULL to prevent double free
    }

    // Free other structures similarly...
    free(cub);
    cub = NULL; // Set to NULL to prevent double free
}
