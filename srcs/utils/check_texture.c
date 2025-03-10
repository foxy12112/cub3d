/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:18:14 by petrasostar       #+#    #+#             */
/*   Updated: 2025/03/10 11:35:56 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_texture(const char *path, const char *texture_name)
{
    if (!path)  
    {
        ft_error(NULL, "Error: Texture path is NULL");
        return 1;
    }

    if (access(path, F_OK) == -1)  
    {
        ft_error(NULL, "Error: Texture file not found: ");
        ft_error(NULL, texture_name);
        return 1;
    }

    const char *ext = strrchr(path, '.');
    if (!ext || (strcmp(ext, ".xpm") != 0 && strcmp(ext, ".png") != 0))
    {
        ft_error(NULL, "Error: Invalid texture format: ");
        ft_error(NULL, texture_name);
        return 1;
    }

    return 0; // Texture is valid
}

