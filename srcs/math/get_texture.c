/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:51:44 by psostari          #+#    #+#             */
/*   Updated: 2025/04/15 10:02:02 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// mlx_image_t	*get_wall_texture(t_cub_data *cub)
// {
// 	if (cub-> side == 0)
// 		return (cub->texture->no_tex);
// 	else if (cub-> side == 1)
// 		return (cub->texture->so_tex);
// 	else if (cub->side == 2)
// 		return (cub->texture->we_tex);
// 	else if (cub->side == 3)
// 		return (cub->texture->ea_tex);
// 	return (NULL);
// }

// void	detect_wall_side(t_cub_data *cub, double ray_dir_x, double ray_dir_y, int hit_vertical)
// {
// 	if (hit_vertical) //for vertical line east/west
// 	{
// 		if (ray_dir_x > 0) //east
// 			cub->side = 3;
// 		else
// 		cub->side = 2; //west
// 	}
// 	else //if it hits horizonta; line (north/south)
// 	{
// 		if (ray_dir_y > 0)
// 			cub->side = 1;
// 		else
// 			cub->side = 0;
// 	}
// }

// void detect_wall_side(t_cub_data *cub, double ray_dir_x, double ray_dir_y, int hit_vertical)
// {
//     if (hit_vertical) // Za vertikalne linije (istok/zapad)
//     {
//         if (ray_dir_x > 0)
//             cub->side = 3; // Istočna strana
//         else
//             cub->side = 2; // Zapadna strana
//     }
//     else // Za horizontalne linije (sjever/jug)
//     {
//         if (ray_dir_y > 0)
//             cub->side = 1; // Južna strana
//         else
//             cub->side = 0; // Sjeverna strana
//     }
// }

// void	draw_textured_wall(int x, int drawStart, int drawEnd, t_cub_data *cub)
// {
// 	mlx_image_t		*texture;
// 	int				tex_x;
// 	int				tex_y;
// 	double			tex_step;
// 	double			tex_pos;
// 	int				y;
// 	int				color;

// 	texture = get_wall_texture(cub);
// 	if (texture == NULL)
// 		return ;
// 	tex_x = (int)(cub->wallX * (double)texture->width);
// 	tex_step = 1.0 * texture->height / (drawEnd - drawStart);
// 	tex_pos = (drawStart - cub->mlx->height / 2 + \
// 	(drawEnd - drawStart) / 2) * tex_step;
// 	y = drawStart;
// 	while (y < drawEnd)
// 	{
// 		tex_y = (int)tex_pos & (texture->height - 1);
// 		tex_pos += tex_step;
// 		color = get_pixel_color(texture, tex_x, tex_y);
// 		mlx_put_pixel(cub->img, x, y, color);
// 		y++;
// 	}
// }

// double	calculate_wallX(t_cub_data *cub, double perpWallDist)
// {
// 	double	wallX;

// 	if (cub->side == 0 || cub->side == 1)
// 	{
// 		wallX = cub->p->y + perpWallDist * cub->ray_dir_y;
// 	}
// 	else
// 	{
// 		wallX = cub->p->x + perpWallDist * cub->ray_dir_x;
// 	}
// 	wallX -= floor(wallX);
// 	return (wallX);
}
void init_player(t_cub_data *cub)
{
    // Set the player's starting position (example: map coordinates 13, 3)
    cub->p->x = 13.0; // Player's x position
    cub->p->y = 3.0;  // Player's y position

    // Set the player's initial direction (example: facing north)
    cub->p->dir_x = 0;
    cub->p->dir_y = -1;

    // Set the camera plane (perpendicular to the direction vector)
    cub->p->plane_x = 0.66; // Adjust for FOV (field of view)
    cub->p->plane_y = 0;

    // Debugging output to verify initialization
    printf("Player initialized:\n");
    printf("Position: (%f, %f)\n", cub->p->x, cub->p->y);
    printf("Direction: (%f, %f)\n", cub->p->dir_x, cub->p->dir_y);
    printf("Camera plane: (%f, %f)\n", cub->p->plane_x, cub->p->plane_y);
}
