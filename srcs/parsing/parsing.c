/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:55:37 by ldick             #+#    #+#             */
/*   Updated: 2025/03/10 08:12:30 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parsing(t_cub_data *cub)
{
    // We check the folder first - if it exists, if the player is present, and if it is closed
    if (check_map(cub) != 0)
        return ft_error(cub, "Error in map parsing"), 1;

    // We check the textures after ensuring that the map exists and is correct
    if (check_textures(cub) != 0)
        return ft_error(cub, "Error in texture parsing"), 1;

    // We check the length of the lines on the map
    if (check_row(cub) != 0)
        return ft_error(cub, "Inconsistent row lengths in map"), 1;

    // We are checking for invalid characters on the map
    if (check_invalid_chars(cub) != 0)
        return ft_error(cub, "Invalid character in map"), 1;

    // We are checking the minimum folder size
    if (check_map_dim(cub) != 0)
        return ft_error(cub, "Map is too small, must be at least 3x3"), 1;

    return (SUCCESS);
}

int check_invalid_chars(t_cub_data *cub)
{
    int y = 0;
    int x;

    while (cub->map[y]) {
        x = 0;
        while (cub->map[y][x]) {
            if (cub->map[y][x] != '1' && cub->map[y][x] != '0' && cub->map[y][x] != 'N' && 
                cub->map[y][x] != 'S' && cub->map[y][x] != 'E' && cub->map[y][x] != 'W' &&
                cub->map[y][x] != ' ' && cub->map[y][x] != '\t'){
                return ft_error(cub, "Invalid character in map"), FAILURE;
            }
            x++;
        }
        y++;
    }
    return (0);
}

int check_row(t_cub_data *cub)
{
    int y = 0;
    int row_length = ft_strlen(cub->map[0]);

    while (cub->map[y])
    {
        // If the current line is not the same length as the first, return an error
        if ((int)ft_strlen(cub->map[y]) != row_length)
        {
            ft_error(cub, "Inconsistent row lengths in map");
            return 1;
        }
        y++;
    }

    return (0);
}