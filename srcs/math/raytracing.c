/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:48:44 by psostari          #+#    #+#             */
/*   Updated: 2025/03/31 10:46:10 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// include "cub3d.h"

// static int	ray_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int	dx = x1 - x0;
// 	int	dy = y1 - y0;
// 	double	step_x = (dx > 0) ? 2 : -2;
// 	double	step_y = (dy > 0) ? 2 : -2;
// 	dx = ft_abs(dx);
// 	dy = ft_abs(dy);
// 	int start_x = x0;
// 	int start_y = y0;
// 	int	p = 2 * dy - dx;
// 	int	i = 0;

// 	while (i <= dx && !touch(x0 - 50, y0 - 50, cub))
// 	{
// 		if (p >= 0)
// 		{
// 			y0 += step_y;
// 			p -= 2 * dx;
// 		}
// 		p += 2 * dy;
// 		x0 += step_x;
// 		i++;
// 	}
// 	double dlen = sqrt(pow(x0 - start_x, 2) + pow(y0 - start_y, 2));
// 	// printf("%f\n", dlen);
// 	return (int)dlen;
// }

// static int	ray_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int	dx = x1 - x0;
// 	int	dy = y1 - y0;
// 	int	dx_abs = ft_abs(dx);
// 	int	dy_abs = ft_abs(dy);
// 	int	start_x = x0;
// 	int	start_y = y0;
// 	double	step_x = (dx > 0) ? 2 : -2;
// 	double	step_y = (dy > 0) ? 2 : -2;
// 	int	p = 2 * dx_abs - dy_abs;
// 	int	i = 0;
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
// 	double dlen = sqrt(pow(x0 - start_x, 2) + pow(y0 - start_y, 2));
// 	// printf("%f\n", dlen);
// 	return (int)dlen;
// }

// static int	ray(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);

// 	if (dx >= dy)
// 		return (ray_x(x0, y0, x1, y1, cub));
// 	else
// 		return(ray_y(x0, y0, x1, y1, cub));
// }

// void	draw_v_line(int x, int start, int end, mlx_image_t *img)
// {
// 	while(start++ < end)
// 	{
// 		mlx_put_pixel(img, x, start, 0x4514ffff);
// 	}
// }

// void	draw_game(int x, double ray_d, t_cub_data *cub)
// {
// 	double line_hight = ((cub->img->height) - (ray_d * 6));
// 	// printf("--%f--\n", ray_d);
// 	if (line_hight >= cub->mlx->height)
// 		line_hight = cub->mlx->height;
// 	// printf("%d\n", line_hight);
// 	int	draw_start = (-line_hight / 2) + (cub->img->height / 2);
// 	draw_start = (draw_start < 0) ? 0 : draw_start;
// 	int draw_end = (line_hight / 2) + (cub->img->height / 2);
// 	if (draw_end >= cub->mlx->height)
// 		draw_end = cub->mlx->height - 1;
// 	// ft_swap(&draw_end, &draw_start, sizeof(int));
// 	// printf("%d--%d--%d--%d\n", x, draw_start, draw_end, 1);
// 	// printf("%d--%d\n", draw_end, draw_start);
// 	draw_v_line(x, draw_start, draw_end, cub->img);
// // 	double	height;
// // 	int	start;
// // 	int	end;

// // 	height = (ray_d / 64) * (WIDHT / 2);
// // 	start = (HEIGHT - height) / 2;
// // 	end = start + height;
// // 	if (end >= HEIGHT)
// // 		end = HEIGHT - 1;
// // 	if (start <= 0)
// // 		start = 1;
// // 	// printf("x=%d--heihgt=%f--start=%d--end=%d--img-height=%d--img-widht=%d\n",x,  height, start, end, cub->img->height, cub->img->width);
// // 	draw_v_line(x, start, end, cub->img);
// }

// int	raytrace(t_cub_data *cub)
// {
// 	int x1;
// 	int y1;
// 	int x;
// 	int y;
// 	double angle;
// 	double	i;
// 	double dir;
// 	int temp = 0;
// 	dir = cub->p->dir;
// 	i = 0;
// 	int tmp;
// 	draw_c_f(cub);
// 	int step = 1;
// 	while(i < (double)FOV)
// 	{
// 		angle = dir * (M_PI / 180);
// 		x1 = cub->minimap->p_img->instances[0].x + 5;
// 		y1 = cub->minimap->p_img->instances[0].y + 5;
// 		x = x1 + cos(angle - M_PI_2) * 500;
// 		y = y1 + sin(angle - M_PI_2) * 500;
// 		int ray_d = ray(x1, y1, x, y, cub);
// 		// printf("ray-length=%d--ray_number=%0f\n", ray_d, i);
// 		tmp = temp + (cub->mlx->width / (FOV * step));
// 		while(temp < tmp)
// 		{
// 			// printf("%d--%d\n", temp, tmp);
// 			draw_game(temp, ray_d, cub);
// 			temp++;
// 		}
// 		i += 1;
// 		dir += 0.5;
// 	}
// 	return (1);
// }

// static int ray_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
//     int dx;
//     int dy;
//     int dx_abs;
//     int dy_abs;
//     int step_x;
//     int step_y;
//     int p;
//     int i;
//     double dlen;

//     dx = x1 - x0;
//     dy = y1 - y0;
//     dx_abs = ft_abs(dx);
//     dy_abs = ft_abs(dy);
//     step_x = 1;
//     if (dx <= 0)
//         step_x = -1;
//     step_y = 1;
//     if (dy <= 0)
//         step_y = -1;
//     p = 2 * dy_abs - dx_abs;
//     i = 0;
    
//     while (i <= dx_abs)
//     {
//         if (p >= 0)
//         {
//             y0 += step_y;
//             p -= 2 * dx_abs;
//         }
//         p += 2 * dy_abs;
//         x0 += step_x;

//         if (touch(x0 - 50, y0 - 50, cub))
//             break;
        
//         i++;
//     }
//     dlen = sqrt(dx_abs * dx_abs + dy_abs * dy_abs);
//     return (int)dlen;
// }

// static int ray_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
//     int dx;
//     int dy;
//     int dx_abs;
//     int dy_abs;
//     int step_x;
//     int step_y;
//     int p;
//     int i;
//     double dlen;

//     dx = x1 - x0;
//     dy = y1 - y0;
//     dx_abs = ft_abs(dx);
//     dy_abs = ft_abs(dy);
//     step_x = 1;
//     if (dx <= 0)
//         step_x = -1;
//     step_y = 1;
//     if (dy <= 0)
//         step_y = -1;
//     p = 2 * dx_abs - dy_abs;
//     i = 0;
    
//     while (i <= dy_abs)
//     {
//         if (p >= 0)
//         {
//             x0 += step_x;
//             p -= 2 * dy_abs;
//         }
//         p += 2 * dx_abs;
//         y0 += step_y;

//         if (touch(x0 - 50, y0 - 50, cub))
//             break;
        
//         i++;
//     }
//     dlen = sqrt(dx_abs * dx_abs + dy_abs * dy_abs);
//     return (int)dlen;
// }

// static int ray(int x0, int y0, int x1, int y1, t_cub_data *cub)
// {
//     int dx;
//     int dy;

//     dx = abs(x1 - x0);
//     dy = abs(y1 - y0);
    
//     if (dx >= dy)
//         return ray_x(x0, y0, x1, y1, cub);
//     return ray_y(x0, y0, x1, y1, cub);
// }

// void draw_v_line(int x, int start, int end, mlx_image_t *img)
// {
//     while (start++ < end)
//     {
//         mlx_put_pixel(img, x, start, 0x4514ffff);
//     }
// }

// void draw_game(int x, double ray_d, t_cub_data *cub)
// {
//     double corrected_ray_d;
//     double line_height;
//     int draw_start;
//     int draw_end;
    
//     corrected_ray_d = ray_d * cos(cub->p->dir - cub->p->camera_angle);
//     line_height = (cub->mlx->height / corrected_ray_d);
    
//     if (line_height > cub->mlx->height)
//         line_height = cub->mlx->height;
    
//     draw_start = (cub->mlx->height / 2) - (line_height / 2);
//     draw_end = (cub->mlx->height / 2) + (line_height / 2);
    
//     if (draw_start < 0)
//         draw_start = 0;
//     if (draw_end >= cub->mlx->height)
//         draw_end = cub->mlx->height - 1;
    
//     draw_v_line(x, draw_start, draw_end, cub->img);
// }

// int raytrace(t_cub_data *cub)
// {
//     int x1;
//     int y1;
//     int x;
//     int y;
//     double angle;
//     double dir;
//     double i;
//     int tmp;
//     int temp;
//     int step;
//     int ray_d;
    
//     dir = cub->p->dir;
//     i = 0;
//     temp = 0;
//     step = 1;
    
//     draw_c_f(cub);
    
//     while (i < FOV)
//     {
//         angle = dir * (M_PI / 180);
        
//         x1 = cub->minimap->p_img->instances[0].x + 5;
//         y1 = cub->minimap->p_img->instances[0].y + 5;
        
//         x = x1 + cos(angle - M_PI_2) * 500;
//         y = y1 + sin(angle - M_PI_2) * 500;
        
//         ray_d = ray(x1, y1, x, y, cub);
        
//         tmp = temp + (cub->mlx->width / (FOV * step));
        
//         while (temp < tmp)
//         {
//             draw_game(temp, ray_d, cub);
//             temp++;
//         }
        
//         i += 1;
//         dir += 0.5;
//     }
//     return 1;
// }

static double calculate_perp_dist(double sideDistX, double deltaDistX, double sideDistY, double deltaDistY, int side)
{
    double perpWallDist;

    if (side == 0)
        perpWallDist = sideDistX - deltaDistX;
    else
        perpWallDist = sideDistY - deltaDistY;

    return (perpWallDist);
}

static int ray_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
    int dx;
    int dy;
    int dx_abs;
    int dy_abs;
    int step_x;
    int step_y;
    int p;
    int i;
    double dlen;

    dx = x1 - x0;
    dy = y1 - y0;
    dx_abs = ft_abs(dx);
    dy_abs = ft_abs(dy);
    if (dx > 0)
        step_x = 2;
    else
        step_x = -2;
    if (dy > 0)
        step_y = 2;
    else
        step_y = -2;
    p = 2 * dy_abs - dx_abs;
    i = 0;
    while (i <= dx_abs && !touch(x0 - 50, y0 - 50, cub))
	{
		if (p >= 0)
		{
			y0 += step_y;
			p -= 2 * dx_abs;
		}
		p += 2 * dy_abs;
		x0 += step_x;
		i++;
	}
    dlen = sqrt(dx_abs * dx_abs + dy_abs * dy_abs);
    return ((int)dlen);
}

static int ray_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
    int dx;
    int dy;
    int dx_abs;
    int dy_abs;
    int step_x;
    int step_y;
    int p;
    int i;
    double dlen;

    dx = x1 - x0;
    dy = y1 - y0;
    dx_abs = ft_abs(dx);
    dy_abs = ft_abs(dy);
    if (dx > 0)
        step_x = 2;
    else
        step_x = -2;
    if (dy > 0)
        step_y = 2;
    else
        step_y = -2;
    p = 2 * dx_abs - dy_abs;
    i = 0;
    while (i <= dy_abs && !touch(x0 - 50, y0 - 50, cub))
    {
        if (p >= 0)
        {
            x0 += step_x;
            p -= 2 * dy_abs;
        }
        p += 2 * dx_abs;
        y0 += step_y;
        i++;
    }
    dlen = sqrt(dx_abs * dx_abs + dy_abs * dy_abs);
    return ((int)dlen);
}

static int ray(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
    int dx;
    int dy;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    if (dx >= dy)
    {
        return ray_x(x0, y0, x1, y1, cub);
    }
    return ray_y(x0, y0, x1, y1, cub);
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
    double corrected_ray_d;
    double line_height;
    int draw_start;
    int draw_end;

    corrected_ray_d = ray_d * cos(cub->p->dir - cub->p->camera_angle);
    line_height = (cub->mlx->height / corrected_ray_d);
    if (line_height > cub->mlx->height)
    {
        line_height = cub->mlx->height;
    }
    draw_start = (cub->mlx->height / 2) - (line_height / 2);
    draw_end = (cub->mlx->height / 2) + (line_height / 2);
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

int raytrace(t_cub_data *cub)
{
    int x1;
    int y1;
    int x;
    int y;
    double angle;
    double dir;
    int temp;
    int step;
    int ray_d;
    int i;
    int tmp;
    
    dir = cub->p->dir;
    temp = 0;
    step = 1;
    draw_c_f(cub);
    i = 0;
    while (i < FOV)
    {
        angle = dir * (M_PI / 180);
        x1 = cub->minimap->p_img->instances[0].x + 5;
        y1 = cub->minimap->p_img->instances[0].y + 5;
        x = x1 + cos(angle - M_PI_2) * 500;
        y = y1 + sin(angle - M_PI_2) * 500;
        ray_d = ray(x1, y1, x, y, cub);
        tmp = temp + (cub->mlx->width / (FOV * step));
        while (temp < tmp)
        {
            draw_game(temp, ray_d, cub);
            temp++;
        }
        i++;
        dir += 0.5;
    }
    return (1);
}
