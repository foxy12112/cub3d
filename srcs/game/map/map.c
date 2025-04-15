/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:08:20 by ldick             #+#    #+#             */
/*   Updated: 2025/04/15 12:01:28 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_cub_data *cub, int x, int y, int rec_size)
{
	int	i;

	i = 0;
	while (i < rec_size)
	{
		mlx_put_pixel(cub->minimap->img, (x + 1) * (rec_size + 2) - 2, \
		y * (rec_size + 2) + i, 0x545454fa);
		mlx_put_pixel(cub->minimap->img, (x + 1) * (rec_size + 2) - 1, \
		y * (rec_size + 2) + i, 0x545454fa);
		i++;
	}
	i = 0;
	while (i < rec_size)
	{
		mlx_put_pixel(cub->minimap->img, x * (rec_size + 2) + i, (y + 1) * \
		(rec_size + 2) - 2, 0x545454fa);
		mlx_put_pixel(cub->minimap->img, x * (rec_size + 2) + i, (y + 1) * \
		(rec_size + 2) - 1, 0x545454fa);
		i++;
	}
}

void	draw_square(t_cub_data *cub, int wall, int x, int y, int rec_size)
{
	int			color;
	int			i;
	int			j;

	j = 0;
	i = 0;
	color = wall ? 0xb56641ff : 0x747878ff;
	draw_wall(cub, x, y, rec_size);
	while (i < rec_size)
	{
		while (j < rec_size)
		{
			mlx_put_pixel(cub->minimap->img, x * (rec_size + 2) \
			+ i, y * (rec_size + 2) + j, color);
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
	while (cub->map[y])
	{
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1' || cub->map[y][x] == ' ')
				draw_square(cub, 1, x, y, RECTANGLE);
			else
				draw_square(cub, 0, x, y, RECTANGLE);
			x++;
		}
		x = 0;
		y++;
	}
}

void calculate_size(t_cub_data *cub)
{
	float	size_x = cub->minimap->size_x * 22;
	float	size_y = cub->minimap->size_y * 22;
	float	max_width = cub->mlx->width / 4;
	float	max_height = cub->mlx->height / 4;

	while (size_x >= max_width || size_y >= max_height)
	{
		size_x /= 2;
		size_y /= 2;
	}
	cub->minimap->scale = (size_x / 22 > size_y / 22) ? (size_x / 22) : (size_y / 22);
	printf("Minimap size: %f x %f\n", size_x, size_y);
}

void draw_rays(t_cub_data *cub)
{
    int x;
    double ray_dir_x;
    double ray_dir_y;
    double ray_pos_x;
    double ray_pos_y;
    double step_size = 0.1; // Step size for ray traversal
    int hit;

    x = 0;
    while (x < cub->mlx->width) // Cast a ray for each column
    {
        // Calculate ray direction
        double cameraX = 2 * x / (double)cub->mlx->width - 1;
        ray_dir_x = cub->p->dir_x + cub->p->plane_x * cameraX;
        ray_dir_y = cub->p->dir_y + cub->p->plane_y * cameraX;

        // Start ray at player's position
        ray_pos_x = cub->p->x;
        ray_pos_y = cub->p->y;

        hit = 0;
        while (!hit)
        {
            // Move the ray forward
            ray_pos_x += ray_dir_x * step_size;
            ray_pos_y += ray_dir_y * step_size;

            // Check if the ray hits a wall
            if (cub->map[(int)ray_pos_y][(int)ray_pos_x] == '1')
                hit = 1;

            // Draw the ray on the minimap
            mlx_put_pixel(cub->minimap->img, ray_pos_x * cub->minimap->scale, ray_pos_y * cub->minimap->scale, 0xFF0000FF); // Red for rays
        }
        x++;
    }
}

void	map(t_cub_data *cub)
{
	int	max_row_length;
	int	y;
	int	row_length;

	max_row_length = 0;
	y = 0;
	while (cub->map[y])
	{
		row_length = 0;
		while (cub->map[y][row_length])
			row_length++;
		if (row_length > max_row_length)
			max_row_length = row_length;
		y++;
	}
	cub->minimap->size_x = max_row_length;
	cub->minimap->size_y = 0;
	while (cub->map[cub->minimap->size_y])
		cub->minimap->size_y++;
	printf("Map dimensions: %d (width) x %d (height)\n", cub->minimap->size_x, cub->minimap->size_y);
	cub->minimap->scale_x = cub->mlx->width / (double)cub->minimap->size_x;
	cub->minimap->scale_y = cub->mlx->height / (double)cub->minimap->size_y;
	calculate_size(cub);
	printf("Minimap scale: %.2f\n", cub->minimap->scale);
	cub->minimap->img = mlx_new_image(cub->mlx, cub->mlx->width, cub->mlx->height);
	if (!cub->minimap->img)
	{
		printf("Error: Failed to create minimap image.\n");
		return ;
	}
	mlx_image_to_window(cub->mlx, cub->minimap->img, 50, 50);
	draw_map(cub);
	cub->p->x = (double)cub->p->start_x;
	cub->p->y = (double)cub->p->start_y;
	printf("Player starting position: %.6f, %.6f\n", cub->p->x, cub->p->y);
}

