/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:48:44 by psostari          #+#    #+#             */
/*   Updated: 2025/04/14 12:50:10 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void init_ray_direction(t_cub_data *cub, int x)
// {
// 	double	cameraX;

// 	cameraX = 2 * x / (double)cub->mlx->width - 1;
// 	cub->ray_dir_x = cub->p->dir_x + cub->p->plane_x * cameraX;
// 	cub->ray_dir_y = cub->p->dir_y + cub->p->plane_y * cameraX;
// 	printf("x: %d, cameraX: %f, ray_dir_x: %f, ray_dir_y: %f\n", x, cameraX, cub->ray_dir_x, cub->ray_dir_y);
// }

void init_ray_direction(t_cub_data *cub, int x)
{
    double cameraX;

    // Map x-coordinate to range [-1, 1]
    cameraX = 2 * x / (double)cub->mlx->width - 1;

    // Calculate ray direction
    cub->ray_dir_x = cub->p->dir_x + cub->p->plane_x * cameraX;
    cub->ray_dir_y = cub->p->dir_y + cub->p->plane_y * cameraX;

    // Debugging output
    printf("Column: %d, cameraX: %f\n", x, cameraX);
    printf("Ray direction: (%f, %f)\n", cub->ray_dir_x, cub->ray_dir_y);
}

// static int ray_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int	dx;
// 	int	dy;
// 	int	dx_abs;
// 	int	dy_abs;
// 	int	step_x;
// 	int	step_y;
// 	int	p;
// 	int	i;
// 	double	dlen;

// 	dx = x1 - x0;
// 	dy = y1 - y0;
// 	dx_abs = ft_abs(dx);
// 	dy_abs = ft_abs(dy);
// 	if (dx > 0)
// 		step_x = 2;
// 	else
// 		step_x = -2;
// 	if (dy > 0)
// 		step_y = 2;
// 	else
// 		step_y = -2;
// 	p = 2 * dy_abs - dx_abs;
// 	i = 0;
// 	while (i <= dx_abs && !touch(x0 - 50, y0 - 50, cub))
// 	{
// 		if (p >= 0)
// 		{
// 			y0 += step_y;
// 			p -= 2 * dx_abs;
// 		}
// 		p += 2 * dy_abs;
// 		x0 += step_x;
// 		i++;
// 	}
// 	dlen = sqrt(dx_abs * dx_abs + dy_abs * dy_abs);
// 	return ((int)dlen);
// }

// static int	ray_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int	dx;
// 	int	dy;
// 	int	dx_abs;
// 	int	dy_abs;
// 	int	step_x;
// 	int	step_y;
// 	int	p;
// 	int	i;
// 	double	dlen;

// 	dx = x1 - x0;
// 	dy = y1 - y0;
// 	dx_abs = ft_abs(dx);
// 	dy_abs = ft_abs(dy);
// 	if (dx > 0)
// 		step_x = 2;
// 	else
// 		step_x = -2;
// 	if (dy > 0)
// 		step_y = 2;
// 	else
// 		step_y = -2;
// 	p = 2 * dx_abs - dy_abs;
// 	i = 0;
// 	while (i <= dy_abs && !touch(x0 - 50, y0 - 50, cub))
// 	{
// 		if (p >= 0)
// 		{
// 			x0 += step_x;
// 			p -= 2 * dy_abs;
// 		}
// 		p += 2 * dx_abs;
// 		y0 += step_y;
// 		i++;
// 	}
// 	dlen = sqrt(dx_abs * dx_abs + dy_abs * dy_abs);
// 	return ((int)dlen);
// }

// static int	ray(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int	dx;
// 	int	dy;
// 	int	hit_vertical; // 1 = hit on the vetical l. 0 = horizontal
// 	dx = abs(x1 - x0);
// 	dy = abs(y1 - y0);
// 	if (dx >= dy)
// 	{
// 		hit_vertical = 1; // hit is on the vertical line
// 		detect_wall_side(cub, cub->ray_dir_x, cub->ray_dir_y, hit_vertical);
// 		return (ray_x(x0, y0, x1, y1, cub));
// 	}
// 	else
// 	{
// 		hit_vertical = 0; // on the horizontal l.
// 		detect_wall_side(cub, cub->ray_dir_x, cub->ray_dir_y, hit_vertical);
// 		return (ray_y(x0, y0, x1, y1, cub));
// 	}
// }

// static int	ray(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int	dx = abs(x1 - x0);
// 	int	dy = abs(y1 - y0);
// 	int	hit_vertical;

// 	printf("Ray start: (%d, %d), Ray direction: (%d, %d)\n", x0, y0, x1, y1);
// 	if (dx >= dy)
// 	{
// 		hit_vertical = 1;
// 		detect_wall_side(cub, cub->ray_dir_x, cub->ray_dir_y, hit_vertical);
// 		return ray_x(x0, y0, x1, y1, cub);
// 	}
// 	else
// 	{
// 		hit_vertical = 0;
// 		detect_wall_side(cub, cub->ray_dir_x, cub->ray_dir_y, hit_vertical);
// 		return ray_y(x0, y0, x1, y1, cub);
// 	}
// }

double ray(double posX, double posY, double rayDirX, double rayDirY, t_cub_data *cub)
{
    int mapX = (int)posX;
    int mapY = (int)posY;

    double sideDistX;
    double sideDistY;

    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);
    double perpWallDist;

    int stepX;
    int stepY;
    int hit = 0; // Was a wall hit?
    int side;    // Was the wall vertical or horizontal?

    // Calculate step and initial sideDist
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    // Perform DDA
    while (hit == 0)
    {
        // Jump to the next map square, either in x-direction or y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        // Check if the ray has hit a wall
        if (cub->map[mapX][mapY] == '1') // Assuming '1' represents a wall
            hit = 1;
    }

    // Debugging output
    printf("Ray hit at map position: (%d, %d)\n", mapX, mapY);

    // Calculate perpendicular wall distance
    if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

    return perpWallDist;
}

void draw_v_line(int x, int start, int end, mlx_image_t *img)
{
	while (start < end)
	{
		mlx_put_pixel(img, x, start, 0x4514ffff);
		start++;
	}
}

void draw_game(int x, double ray_d, t_cub_data *cub)
{
	double	corrected_ray_d;
	double	line_height;
	int		draw_start;
	int		draw_end;

	corrected_ray_d = ray_d * cos(cub->p->dir - cub->p->camera_angle);
	line_height = (cub->mlx->height / corrected_ray_d);
	if (line_height > cub->mlx->height)
	{
		line_height = cub->mlx->height;
	}
	draw_start = (cub->mlx->height / 2) - (line_height / 2);
	draw_end = (line_height / 2) + (cub->mlx->height / 2);
	if (draw_start < 0)
	{
		draw_start = 0;
	}
	if (draw_end >= cub->mlx->height)
	{
		draw_end = cub->mlx->height - 1;
	}
	draw_v_line(x, draw_start, draw_end, cub->img);
}

// void	raytrace(t_cub_data *cub)
// {
// 	int	x;
// 	double	perpWallDist;
// 	int	lineHeight;
// 	int	drawStart, drawEnd;

// 	x = 0;
// 	draw_c_f(cub);
// 	while (x < cub->mlx->width)
// 	{
// 		init_ray_direction(cub, x);
// 		perpWallDist = ray(cub->p->x, cub->p->y, cub->ray_dir_x, \
// 			cub->ray_dir_y, cub);
// 		cub->wallX = calculate_wallX(cub, perpWallDist);
// 		lineHeight = (int)(cub->mlx->height / perpWallDist);
// 		drawStart = -lineHeight / 2 + cub->mlx->height / 2;
// 		drawEnd = lineHeight / 2 + cub->mlx->height / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		if (drawEnd >= cub->mlx->height)
// 			drawEnd = cub->mlx->height - 1;
// 		if (get_wall_texture(cub) != NULL)
// 		{
// 			draw_textured_wall(x, drawStart, drawEnd, cub);
// 		}
// 		else
// 		{
// 			draw_game(x, perpWallDist, cub);
// 		}
// 		x++;
// 	}
// }

void raytrace(t_cub_data *cub)
{
    int x;
    double perpWallDist;
    int lineHeight;
    int drawStart, drawEnd;

    x = 0;
    draw_c_f(cub); // Draw ceiling and floor
    while (x < cub->mlx->width)
    {
        init_ray_direction(cub, x);

        // Debugging output
        printf("Raycasting column %d\n", x);
        printf("Player position: (%f, %f)\n", cub->p->x, cub->p->y);
        printf("Ray direction: (%f, %f)\n", cub->ray_dir_x, cub->ray_dir_y);

        perpWallDist = ray(cub->p->x, cub->p->y, cub->ray_dir_x, cub->ray_dir_y, cub);
        printf("Perpendicular wall distance: %f\n", perpWallDist);

        lineHeight = (int)(cub->mlx->height / perpWallDist);
        drawStart = -lineHeight / 2 + cub->mlx->height / 2;
        drawEnd = lineHeight / 2 + cub->mlx->height / 2;

        if (drawStart < 0)
            drawStart = 0;
        if (drawEnd >= cub->mlx->height)
            drawEnd = cub->mlx->height - 1;

        draw_game(x, perpWallDist, cub);
        x++;
    }
}
