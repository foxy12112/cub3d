/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/02/13 10:46:47 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_c_f(t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < cub->mlx->height / 2)
	{
		while(j < cub->mlx->width)
		{
			mlx_put_pixel(cub->img, j, i, cub->ceiling);
			j++;
		}
		j = 0;
		i++;
	}
	while(i < cub->mlx->height)
	{
		while(j < cub->mlx->width)
		{
			mlx_put_pixel(cub->img, j, i, cub->floor);
			j++;
		}
		j = 0;
		i++;
	}
}

void resize_callback(int32_t width, int32_t height, void* param)
{
	t_cub_data *cub = param;

	draw_c_f(cub);
	printf("Window resized to width: %d, height: %d\n", width, height);
}

// void	add_images(t_cub_data *#include "cub3d.h"

// Callback function for mlx_loop_hook
int check_wall_collision(void *param)
{
    t_cub_data *cub = (t_cub_data *)param;
    int player_x = (int)cub->p->x; // Player's x position in the map
    int player_y = (int)cub->p->y; // Player's y position in the map

    // Check if the player is touching a wall
    if (cub->map[player_y][player_x] == '1')
    {
        printf("hi\n"); // Player is touching a wall
    }
    else
    {
        printf("bye\n"); // Player is not touching a wall
    }

    return (0); // Return 0 to continue the loop
}

void ft_hook(void* param)
{
    t_cub_data* cub = (t_cub_data*)param;
    // Check for wall collisions
    check_wall_collision(param);

    // Get the player's position on the minimap
    int p_x = cub->minimap->p_img->instances[0].x;
    int p_y = cub->minimap->p_img->instances[0].y;

    // Calculate the player's movement speed based on the minimap scale
    float move_speed = 5.0f; // Base movement speed (in pixels)
    float scale = cub->minimap->scale; // Minimap scale factor

    // Adjust movement speed based on the minimap scale
    float adjusted_speed = move_speed / scale;

    // Handle player movement
    if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
    {
        cub->minimap->p_img->instances[0].y -= move_speed; // Move up on minimap
        cub->p->y -= adjusted_speed; // Update actual player position
    }
    if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
    {
        cub->minimap->p_img->instances[0].y += move_speed; // Move down on minimap
        cub->p->y += adjusted_speed; // Update actual player position
    }
    if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
    {
        cub->minimap->p_img->instances[0].x -= move_speed; // Move left on minimap
        cub->p->x -= adjusted_speed; // Update actual player position
    }
    if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
    {
        cub->minimap->p_img->instances[0].x += move_speed; // Move right on minimap
        cub->p->x += adjusted_speed; // Update actual player position
    }

    // Debug: Print player's position on the minimap and actual map
    printf("Minimap position: (%d, %d)\n", p_x, p_y);
    printf("Actual position: (%.2f, %.2f)\n", cub->p->x, cub->p->y);
}

void	game_loop(t_cub_data *cub)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	cub->mlx = mlx_init(2880, 1620, "cub3d", true);
	cub->ceiling = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 255);
	cub->floor = get_color(cub->texture->floor->r, cub->texture->floor->g, cub->texture->floor->b, 255);
	cub->img = mlx_new_image(cub->mlx, 2880, 1620);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	cub->img->instances->z = 0;
	map(cub);
	draw_player(cub);
	draw_textbox(cub);
	mlx_resize_hook(cub->mlx, &resize_callback, cub);
	mlx_key_hook(cub->mlx, event, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}