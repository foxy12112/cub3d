/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:52:10 by petrasostar       #+#    #+#             */
/*   Updated: 2025/03/10 08:10:16 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_texture_file(char *path, char *texture_name)
{
    if (path == NULL) // Checking if the path is NULL
    {
        ft_error(NULL, "Error: Texture path is NULL");
        return (1);
    }

    if (open(path, O_RDONLY) == -1) // Checking if the file is available
    {
        ft_error(NULL, "Error opening texture file: ");
        ft_error(NULL, texture_name);
        return (1);
    }

    return (0);
}

int check_textures(t_cub_data *cub)
{
    if (check_texture_file(cub->texture->no, "North texture") == 1)
        return (1);
    if (check_texture_file(cub->texture->so, "South texture") == 1)
        return (1);
    if (check_texture_file(cub->texture->we, "West texture") == 1)
        return (1);
    if (check_texture_file(cub->texture->ea, "East texture") == 1)
        return (1);

    return (0);
}