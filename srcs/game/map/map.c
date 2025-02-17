/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:08:20 by ldick             #+#    #+#             */
/*   Updated: 2025/02/17 18:55:01 by ldick            ###   ########.fr       */
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

// void draw_square(t_cub_data *cub, int wall, int x, int y, double scale)
// {
//     int color;
//     int rect_size;
//     int i;
//     int rgba;

// 	(void)scale;
//     rgba = get_color(88, 84, 84, 240); // Gray color for empty space
//     rect_size = (int)(20); // Fixed size for each block in the minimap
//     color = wall ? 0xffffff : rgba; // White for walls, gray for empty space

//     // Draw the square
//     for (i = 0; i < rect_size; i++)
//     {
//         for (int j = 0; j < rect_size; j++)
//         {
//             mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, y * (rect_size + 2) + j, color);
//         }
//     }

//     // Draw the 2-pixel-wide walls around the square
//     if (wall)
//     {
//         // Draw right wall
//         for (i = 0; i < rect_size; i++)
//         {
//             mlx_put_pixel(cub->minimap->img, (x + 1) * (rect_size + 2) - 2, y * (rect_size + 2) + i, 0xffffff);
//             mlx_put_pixel(cub->minimap->img, (x + 1) * (rect_size + 2) - 1, y * (rect_size + 2) + i, 0xffffff);
//         }

//         // Draw bottom wall
//         for (i = 0; i < rect_size; i++)
//         {
//             mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, (y + 1) * (rect_size + 2) - 2, 0xffffff);
//             mlx_put_pixel(cub->minimap->img, x * (rect_size + 2) + i, (y + 1) * (rect_size + 2) - 1, 0xffffff);
//         }
//     }
// }

void	draw_square(t_cub_data *cub, int wall, int x, int y, int rec_size)
{
	int			color;
	static int	x_true;
	static int	y_true;
	int			i;

	i = 0;
	color = wall ? 0xfffff : 0x585454F0;
	
}

void	draw_map(t_cub_data *cub)
{
	int	x;
	int	y;
	
	y = 0;
	x = 0;
	while(cub->map[y])
	{
		while(cub->map[y][x])
		{
			if (cub->map[y][x] == '1'|| cub->map[y][x] == ' ')
				draw_square(cub, 1, x, y, /*calculate scale first*/ RECTANGLE);
			else
				draw_square(cub, 0, x, y, /*calculate scale first*/ RECTANGLE);
			x++;
		}
		x = 0;
		y++;
	}
}

void	scaling(t_cub_data *cub)
{
	double	size_x;
	double	size_y;
	float	speed;

	size_x = ((double)cub->mlx->width / 100 * 10) * 2;
	size_y = ((double)cub->mlx->height / 100 * 10) * 2;
	speed = (double)cub->mlx->width / (double)cub->mlx->height;
	// printf("%d, %f, %d, %f, speed: %f\n", cub->minimap->size_x, size_x, cub->mlx->width, size_y, speed);
	printf("%f--%f, %d\n", cub->p->x, cub->p->y, cub->minimap->p_img->instances[0].x);
	// mlx_image_t *img = mlx_new_image(cub->mlx, size_x, size_y);
	// mlx_image_to_window(cub->mlx, img, 500, 500);
	// for (int i = 0; i <= size_x; i++)
	// {
	// 	for(int j = 0; j <= size_y; j++)
	// 	{
	// 		mlx_put_pixel(img, i, j, 0xffffff);
	// 	}
	// }
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

	for (int i = cub->minimap->img->instances[0].x + ((cub->p->x + 2) * 20); i < cub->minimap->img->instances[0].x + ((cub->p->x + 2) * 20) + 20; i++)
		for( int j = cub->minimap->img->instances[0].y + ((cub->p->y + 2) * 20); j < cub->minimap->img->instances[0].y + ((cub->p->y + 2) * 20) + 20; j++)
			mlx_put_pixel(cub->minimap->img, i, j, 0x00ff00);
    // Set the player's starting position
    cub->p->x = (double)cub->p->start_x;
    cub->p->y = (double)cub->p->start_y;
    printf("Player starting position: %.6f, %.6f\n", cub->p->x, cub->p->y);
}