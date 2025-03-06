/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:08:20 by ldick             #+#    #+#             */
/*   Updated: 2025/03/06 14:23:44 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_cub_data *cub, int x, int y, int rec_size)
{
	int	i;

	i = 0;
	while(i < rec_size)
	{
		mlx_put_pixel(cub->minimap->img, (x + 1) * (rec_size + 2) - 2, y * (rec_size + 2) + i, 0x545454fa);
		mlx_put_pixel(cub->minimap->img, (x + 1) * (rec_size + 2) - 1, y * (rec_size + 2) + i, 0x545454fa);
		i++;
	}
	i = 0;
	while(i < rec_size)
	{
		mlx_put_pixel(cub->minimap->img, x * (rec_size + 2) + i, (y + 1) * (rec_size + 2) - 2, 0x545454fa);
		mlx_put_pixel(cub->minimap->img, x * (rec_size + 2) + i, (y + 1) * (rec_size + 2) - 1, 0x545454fa);
		i++;
	}
}

void	draw_square(t_cub_data *cub, int wall, int x, int y, int rec_size)
{
	int			color;
	// static int	x_true;
	// static int	y_true;
	int			i;
	int			j;

	j = 0;
	i = 0;
	color = wall ? 0xb56641ff : 0x747878ff;
	draw_wall(cub, x, y, rec_size);
	while(i < rec_size)
	{
		while(j < rec_size)
		{
			mlx_put_pixel(cub->minimap->img, x * (rec_size + 2) + i, y * (rec_size + 2) + j, color);
			j++;
		}
		j = 0;
		i++;
	}
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