/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:43:20 by petrasostar       #+#    #+#             */
/*   Updated: 2025/03/06 17:09:52 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main() {
    t_cub_data cub;  // Initialize the cub data structure
    int result = parsing(&cub);

    // Add the map manually
    cub.map = malloc(4 * sizeof(char *));  // Allocate memory for the map rows
    cub.map[0] = strdup("11111");  // First row of the map (wall)
    cub.map[1] = strdup("1N001");  // Second row with a player at position (1, 'N')
    cub.map[2] = strdup("11111");  // Third row of the map (wall)
    cub.map[3] = NULL;  // End of the map (NULL signifies the end of the map array)
    
    // Set the height and width of the map
    cub.map_height = 3;  // Map height (number of rows)
    cub.map_width = 5;   // Map width (number of columns)

    // Add textures (assuming they are correctly set)
    cub.texture = malloc(sizeof(t_texture_data));  // Allocate memory for the texture structure
    cub.texture->no = strdup("path/to/north_texture");  // North texture path
    cub.texture->so = strdup("path/to/south_texture");  // South texture path
    cub.texture->we = strdup("path/to/west_texture");  // West texture path
    cub.texture->ea = strdup("path/to/east_texture");  // East texture path

    // Initialize the floor and ceiling colors (dummy values for now)
    cub.texture->floor = malloc(sizeof(t_floor_data));
    cub.texture->ceiling = malloc(sizeof(t_ceiling_data));

    cub.texture->floor->r = 255;
    cub.texture->floor->g = 255;
    cub.texture->floor->b = 255;

    cub.texture->ceiling->r = 0;
    cub.texture->ceiling->g = 0;
    cub.texture->ceiling->b = 0;

    // Initialize the player (using your original structure)
    cub.p = malloc(sizeof(t_player_data));  // Allocate memory for the player structure
    cub.p->start_x = 1;  // Player's starting X position in the map
    cub.p->start_y = 1;  // Player's starting Y position in the map
    cub.p->x = 1.0;  // Player's initial X coordinate (floating-point value)
    cub.p->y = 1.0;  // Player's initial Y coordinate (floating-point value)
    cub.p->dir_x = 1.0;  // Player's initial direction vector (X)
    cub.p->dir_y = 0.0;  // Player's initial direction vector (Y)

    // Call the parsing function to check the map, textures, and player data
    result = parsing(&cub);  // Passing the pointer to the 'cub' structure to the parsing function

    // Check the result of the parsing function
    if (result == SUCCESS) {
        printf("Parsing completed successfully!\n");  // If no errors, print success message
    } else {
        printf("Parsing failed with error code: %d\n", result);  // If an error occurs, print the error code
    }

    // Free the dynamically allocated memory for the map and textures
    for (int i = 0; cub.map[i] != NULL; i++) {
        free(cub.map[i]);  // Free each row of the map
    }
    free(cub.map);  // Free the map array itself

    free(cub.texture->no);  // Free the North texture path string
    free(cub.texture->so);  // Free the South texture path string
    free(cub.texture->we);  // Free the West texture path string
    free(cub.texture->ea);  // Free the East texture path string
    free(cub.texture->floor);  // Free the floor data
    free(cub.texture->ceiling);  // Free the ceiling data
    free(cub.texture);  // Free the texture structure

    free(cub.p);  // Free the player structure

    return 0;  // End of the program
}

