/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:08:20 by ldick             #+#    #+#             */
/*   Updated: 2025/02/14 19:37:58 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// // void draw_square(t_cub_data *cub, int wall, int x, int y, double scale)
// // {
// // 	int color;
// // 	int rect_size;
// // 	int i;
// // 	int	rgba;

// // 	rgba = get_color(88, 84, 84, 240);
// // 	i = 0;
// // 	rect_size = (int)(2 * scale);
// // 	color = wall ? 0xffffff : rgba;
// // 	while (i < rect_size)
// // 	{
// // 		int j = 0;
// // 		while (j < rect_size)
// // 		{
// // 			mlx_put_pixel(cub->minimap->img, x * rect_size + i, y * rect_size + j, color);
// // 			j++;
// // 		}
// // 		i++;
// // 	}
// // }

// void draw_square(t_cub_data *cub, int wall, int x, int y, double scale)
// {
// 	int color;
// 	int rect_size;
// 	int i;
// 	int rgba;

// 	(void)scale;
// 	rgba = get_color(88, 84, 84, 240); // Gray color for empty space
// 	rect_size = (int)(20); // Size of each block in the minimap
// 	color = wall ? 0xffffff : rgba; // White for walls, gray for empty space

// 	// Draw the square
// 	for (i = 0; i < rect_size; i++)
// 	{
// 		for (int j = 0; j < rect_size; j++)
// 		{
// 			mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, y * (rect_size + 2) + j, color);
// 		}
// 	}

// 	// Draw the 2-pixel-wide walls around the square
// 	if (wall)
// 	{
// 		// Draw right wall
// 		for (i = 0; i < rect_size; i++)
// 		{
// 			mlx_put_pixel(cub->minimap->img, (x + 1) * (rect_size + 2) - 2, y * (rect_size + 2) + i, 0xffffff);
// 			mlx_put_pixel(cub->minimap->img, (x + 1) * (rect_size + 2) - 1, y * (rect_size + 2) + i, 0xffffff);
// 		}

// 		// Draw bottom wall
// 		for (i = 0; i < rect_size; i++)
// 		{
// 			mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, (y + 1) * (rect_size + 2) - 2, 0xffffff);
// 			mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, (y + 1) * (rect_size + 2) - 1, 0xffffff);
// 		}
// 	}
// }

// void draw_map(t_cub_data *cub)
// {
// 	int x;
// 	int y;

// 	y = 0;
// 	while (y < cub->minimap->size_y) // Iterate through the height of the map
// 	{
// 		x = 0;
// 		while (x < cub->minimap->size_x) // Iterate through the width of the map
// 		{
// 			if (cub->map[y][x] == '1' || cub->map[y][x] == ' ') // Wall or empty space
// 				draw_square(cub, 1, x, y, cub->minimap->scale); // Draw wall
// 			else
// 				draw_square(cub, 0, x, y, cub->minimap->scale); // Draw empty space
// 			x++;
// 		}
// 		y++;
// 	}
// }

// // void	map(t_cub_data *cub)
// // {
// // 	cub->minimap->scale_x = 1000 / (double)cub->minimap->size_x;
// // 	cub->minimap->scale_y = 2000 / (double)cub->minimap->size_y;
// // 	cub->minimap->scale = (cub->minimap->scale_x < cub->minimap->scale_y) ? cub->minimap->scale_x : cub->minimap->scale_y;
// // 	cub->minimap->img = mlx_new_image(cub->mlx, 1000, 2000);
// // 	mlx_image_to_window(cub->mlx, cub->minimap->img, 50, 50);
// // 	draw_map(cub);
// // 	cub->p->x = (double)cub->p->start_x;
// // 	cub->p->y = (double)cub->p->start_y;
// // 	printf("%.6f,--%.6f\n", cub->p->x, cub->p->y);
// // }

// void map(t_cub_data *cub)
// {
//     // Debug: Print map dimensions
//     printf("Map dimensions: %d (width) x %d (height)\n", cub->minimap->size_x, cub->minimap->size_y);

//     // Calculate the scale of the minimap
//     cub->minimap->scale_x = 1000 / (double)cub->minimap->size_x; // Width of minimap
//     cub->minimap->scale_y = 2000 / (double)cub->minimap->size_y; // Height of minimap
//     cub->minimap->scale = (cub->minimap->scale_x < cub->minimap->scale_y) ? cub->minimap->scale_x : cub->minimap->scale_y;

//     // Debug: Print scale
//     printf("Minimap scale: %.2f\n", cub->minimap->scale);

//     // Create the minimap image
//     cub->minimap->img = mlx_new_image(cub->mlx, 1000, 2000);
//     if (!cub->minimap->img)
//     {
//         printf("Error: Failed to create minimap image.\n");
//         return;
//     }
//     mlx_image_to_window(cub->mlx, cub->minimap->img, 50, 50);

//     // Draw the map
//     draw_map(cub);

//     // Set the player's starting position
//     cub->p->x = (double)cub->p->start_x;
//     cub->p->y = (double)cub->p->start_y;
//     printf("Player starting position: %.6f, %.6f\n", cub->p->x, cub->p->y);
// }

void draw_square(t_cub_data *cub, int wall, int x, int y, double scale)
{
    int color;
    int rect_size;
    int i;
    int rgba;

	(void)scale;
    rgba = get_color(88, 84, 84, 240); // Gray color for empty space
    rect_size = (int)(20); // Fixed size for each block in the minimap
    color = wall ? 0xffffff : rgba; // White for walls, gray for empty space

    // Draw the square
    for (i = 0; i < rect_size; i++)
    {
        for (int j = 0; j < rect_size; j++)
        {
            mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, y * (rect_size + 2) + j, color);
        }
    }

    // Draw the 2-pixel-wide walls around the square
    if (wall)
    {
        // Draw right wall
        for (i = 0; i < rect_size; i++)
        {
            mlx_put_pixel(cub->minimap->img, (x + 1) * (rect_size + 2) - 2, y * (rect_size + 2) + i, 0xffffff);
            mlx_put_pixel(cub->minimap->img, (x + 1) * (rect_size + 2) - 1, y * (rect_size + 2) + i, 0xffffff);
        }

        // Draw bottom wall
        for (i = 0; i < rect_size; i++)
        {
            mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, (y + 1) * (rect_size + 2) - 2, 0xffffff);
            mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, (y + 1) * (rect_size + 2) - 1, 0xffffff);
        }
    }
}

void draw_map(t_cub_data *cub)
{
    int x;
    int y;

    y = 0;
    while (cub->map[y]) // Iterate through each row of the map
    {
        x = 0;
        while (cub->map[y][x]) // Iterate through each character in the row
        {
            if (cub->map[y][x] == '1' || cub->map[y][x] == ' ') // Wall or empty space
                draw_square(cub, 1, x, y, cub->minimap->scale); // Draw wall
            else
                draw_square(cub, 0, x, y, cub->minimap->scale); // Draw empty space
            x++;
        }
        y++;
    }
}

void map(t_cub_data *cub)
{
    int max_row_length = 0;

    // Find the maximum row length in the map
    for (int y = 0; cub->map[y]; y++)
    {
        int row_length = 0;
        while (cub->map[y][row_length])
            row_length++;
        if (row_length > max_row_length)
            max_row_length = row_length;
    }

    // Set minimap dimensions
    cub->minimap->size_x = max_row_length; // Width of the minimap
    cub->minimap->size_y = 0;
    while (cub->map[cub->minimap->size_y])
        cub->minimap->size_y++; // Height of the minimap

    // Debug: Print map dimensions
    printf("Map dimensions: %d (width) x %d (height)\n", cub->minimap->size_x, cub->minimap->size_y);

    // Calculate the scale of the minimap
    cub->minimap->scale_x = 1000 / (double)cub->minimap->size_x; // Width of minimap
    cub->minimap->scale_y = 2000 / (double)cub->minimap->size_y; // Height of minimap
    cub->minimap->scale = (cub->minimap->scale_x < cub->minimap->scale_y) ? cub->minimap->scale_x : cub->minimap->scale_y;

    // Debug: Print scale
    printf("Minimap scale: %.2f\n", cub->minimap->scale);

    // Create the minimap image
    cub->minimap->img = mlx_new_image(cub->mlx, 1000, 2000);
    if (!cub->minimap->img)
    {
        printf("Error: Failed to create minimap image.\n");
        return;
    }
    mlx_image_to_window(cub->mlx, cub->minimap->img, 50, 50);

    // Draw the map
    draw_map(cub);

    // Set the player's starting position
    cub->p->x = (double)cub->p->start_x;
    cub->p->y = (double)cub->p->start_y;
    printf("Player starting position: %.6f, %.6f\n", cub->p->x, cub->p->y);
}