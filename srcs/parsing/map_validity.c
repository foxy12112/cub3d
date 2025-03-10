/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:55:55 by petrasostar       #+#    #+#             */
/*   Updated: 2025/03/10 07:41:56 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_exists(t_cub_data *cub)
{
	if (!cub || !cub->map || !cub->map[0])
		return (ft_error(cub, "Map data is invalid"), 1);
	return (0);
}

int check_player(t_cub_data *cub)
{
    int i = 0; // Row index
    int j = 0; // Column index
    int player_count = 0; // Counter for player positions

    // Loop through the map to find the player's position
    while (cub->map[i]) // Iterate over rows of the map
    {
        j = 0; // Reset column index for each row
        while (cub->map[i][j]) // Iterate over columns of the current row
        {
            // Check if the character at this position is one of the possible player directions ('N', 'S', 'E', or 'W')
            if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' ||
                cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
            {
                player_count++; // Increment player count if a direction is found
                cub->p->start_x = j;  // Store the player's X position
                cub->p->start_y = i;  // Store the player's Y position
            }
            j++; // Move to the next column
        }
        i++; // Move to the next row
    }

    // Check that there is exactly one player position in the map
    if (player_count != 1)
    {
        return ft_error(cub, "Multiple or no player positions found"), FAILURE; // If not exactly one player, return an error
    }

    // Initialize the player's actual position as double (for more precise calculations in game)
    cub->p->x = (double)cub->p->start_x; 
    cub->p->y = (double)cub->p->start_y;

    return 0; // Return 0 to indicate success
}

int is_closed(t_cub_data *cub)
{
    // Check if the top of the map is properly closed with walls
    if (check_top(cub) == 1)
        return ft_error(cub, "Map is not properly closed at the top"), FAILURE;

    // Check if the bottom of the map is properly closed with walls
    if (check_bottom(cub) == 1)
        return ft_error(cub, "Map is not properly closed at the bottom"), FAILURE;

    // Check if the sides of the map are properly closed with walls
    if (check_sides(cub) == 1)
        return ft_error(cub, "Map is not properly closed on the sides"), FAILURE;

    // Check for any leaks (open spaces connected to the exterior)
    if (check_leaks(cub->map, cub) == 1)
        return ft_error(cub, "Map has leaks"), FAILURE;

    // If all checks pass, print confirmation and return success
    printf("Map is properly closed :)\n");
    return 0;
}

int check_map(t_cub_data *cub)
{
	if (check_map_exists(cub) == 1)
        return ft_error(cub, "Map does not exist"), FAILURE;
    // Check if the player position is valid and unique
    if (check_player(cub) == 1)
        return ft_error(cub, "Multiple or no player positions found"), FAILURE;
    // Check if the map is properly enclosed with walls
    if (is_closed(cub) == 1)
        return ft_error(cub, "Error: Map is not properly closed"), FAILURE;

    return 0;
}