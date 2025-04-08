/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:29:42 by ldick             #+#    #+#             */
/*   Updated: 2025/04/08 15:51:53 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ray_x(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	double	step_x = (dx > 0) ? 2 : -2;
	double	step_y = (dy > 0) ? 2 : -2;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
	int start_x = x0;
	int start_y = y0;
	int	p = 2 * dy - dx;
	int	i = 0;

	while (i <= dx && !touch(x0 - 50, y0 - 50, cub))
	{
		if (p >= 0)
		{
			y0 += step_y;
			p -= 2 * dx;
		}
		else
		{
		p += 2 * dy;
		x0 += step_x;
		}
		i++;
	}
	double dlen = sqrt(pow(x0 - start_x, 2) + pow(y0 - start_y, 2));
	cub->p->perp_wall_dist = x0 - dx;
	return dlen;
}

static double	ray_y(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	dx_abs = ft_abs(dx);
	int	dy_abs = ft_abs(dy);
	int	start_x = x0;
	int	start_y = y0;
	double	step_x = (dx > 0) ? 2 : -2;
	double	step_y = (dy > 0) ? 2 : -2;
	int	p = 2 * dx_abs - dy_abs;
	int	i = 0;
	while (i <= dy_abs && !touch(x0 - 50, y0 - 50, cub))
	{
		if (p >= 0)
		{
			x0 += step_x;
			p -= 2 * dy_abs;
		}
		else
		{
			p += 2 * dx_abs;
			y0 += step_y;
		}
		i++;
	}
	double dlen = sqrt(pow(x0 - start_x, 2) + pow(y0 - start_y, 2));
	cub->p->perp_wall_dist = y0 - dy;	
	return dlen;
}

static double	ray(int x0, int y0, int x1, int y1, t_cub_data *cub)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
		return (ray_x(x0, y0, x1, y1, cub));
	else
		return(ray_y(x0, y0, x1, y1, cub));
}

// static int	dda_ra_h(int startx, int starty, t_cub_data *cub)
// {
// 	int r,mx,my,mp,dof;
// 	double rx,ry,ra,xo,yo;
// 	ra = cub->p->dir;
// 	r = 0;
// 	while(r < 1)
// 	{
// 		dof = 0;
// 		double atan = -1/(tan(ra));
// 		if (ra > 270 && ra < 90)
// 		{
// 			ry = (((int)cub->p->y >> 6) << 6) - 0.0001;
// 			rx = (cub->p->y - ry) * atan + cub->p->x;
// 			yo = -64;
// 			xo = -yo * atan;
// 		}
// 		if (ra < 270 && ra > 90)
// 		{
// 			ry = (((int)cub->p->y >> 6) << 6) + 64;
// 			rx = (cub->p->y - ry) * atan + cub->p->x;
// 			yo = 64;
// 			xo = -yo * atan;
// 		}
// 		if (ra == 270 || ra == 90)
// 		{
// 			rx = cub->p->x;
// 			ry = cub->p->y;
// 			dof = 8;
// 		}
// 		while( dof < 8)
// 		{
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			mp = my * cub->minimap->size_x + mx;
// 			if (touch(mx, my, cub))
// 				dof = 8;
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof += 1;
// 			}
// 		}
// 		draw_line(cub->minimap->p_img->instances[0].x, cub->minimap->p_img->instances[0].y, mx, my, cub);
// 		r++;
// 	}
// 	double dlen = sqrt(pow(rx - startx, 2) + pow(ry - starty, 2));
// 	return (dlen);
// }

// static int	dda_ra_v(int startx, int starty, t_cub_data *cub)
// {
// 	int r,mx,my,mp,dof;
// 	double rx,ry,ra,xo,yo;
// 	ra = cub->p->dir;
// 	r = 0;
// 	while(r < 1)
// 	{
// 		dof = 0;
// 		double ntan = -tan(ra);
// 		if (ra > 270 && ra < 90)
// 		{
// 			ry = (((int)cub->p->y >> 6) << 6) - 0.0001;
// 			rx = (cub->p->y - ry) * ntan + cub->p->x;
// 			yo = -64;
// 			xo = -yo * ntan;
// 		}
// 		if (ra < 270 && ra > 90)
// 		{
// 			ry = (((int)cub->p->y >> 6) << 6) + 64;
// 			rx = (cub->p->y - ry) * ntan + cub->p->x;
// 			yo = 64;
// 			xo = -yo * ntan;
// 		}
// 		if (ra == 270 || ra == 90)
// 		{
// 			rx = cub->p->x;
// 			ry = cub->p->y;
// 			dof = 8;
// 		}
// 		while( dof < 8)
// 		{
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			mp = my * cub->minimap->size_x + mx;
// 			if (touch(mx, my, cub))
// 				dof = 8;
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof += 1;
// 			}
// 		}
// 		draw_line(cub->minimap->p_img->instances[0].x, cub->minimap->p_img->instances[0].y, mx, my, cub);
// 		r++;
// 	}
// 	double dlen = sqrt(pow(rx - startx, 2) + pow(ry - starty, 2));
// 	return (dlen);
// }


void	draw_v_line(int x, int start, int end, mlx_image_t *img)
{
	int color = (x % 2 == 0) ? 0x4514ffff : 0xffffffff;
	while(start++ < end)
	{
		mlx_put_pixel(img, x, start, color);
	}
}

void	draw_game(int x, double ray_d, t_cub_data *cub)
{
	double line_hight = ((64 / ray_d) * (WIDHT / 2)) + (cub->mlx->height / cub->p->perp_wall_dist);
	// (void)ray_d;
	// int line_hight = (int)(cub->mlx->height / cub->p->perp_wall_dist);
	if (line_hight >= cub->mlx->height)
		line_hight = cub->mlx->height;
	if (line_hight <= 20)
		line_hight = 20;
	int	draw_start = (HEIGHT - line_hight) / 2;
	// draw_start = (draw_start < 0) ? 0 : draw_start;
	int draw_end = (draw_start + line_hight);
	if (draw_end >= cub->mlx->height)
		draw_end = cub->mlx->height - 1;
	draw_v_line(x, draw_start, draw_end, cub->img);
}

int	raytrace(t_cub_data *cub)
{
	double x1;
	double y1;
	double x;
	double y;
	double angle;
	double	i;
	double dir;
	double cameraX, ray_dir_x, ray_dir_y;
	dir = cub->p->dir - 45;
	i = 0;
	draw_c_f(cub);
	double dir_inc = (double)FOV / (double)1920;
	
	// printf("dir_int = %f\n", dir_inc);
	while(i < 1920)
	{
		// cameraX = 2 * x / (double)WIDHT - 1;
		// ray_dir_x = cub->p->dir_x + cub->p->plane_x * cameraX;
		// ray_dir_y = cub->p->dir_y + cub->p->plane_y * cameraX;
		angle = dir * (M_PI / 180);
		x1 = cub->minimap->p_img->instances[0].x + 5;
		y1 = cub->minimap->p_img->instances[0].y + 5;
		x = x1 + cos(angle - M_PI_2) * cub->mlx->width;
		y = y1 + sin(angle - M_PI_2) * cub->mlx->width;
		// printf("%f--%f\n", x, y);
		// double ray_d = ray(x1, y1,x, y, cub);
		double ray_d = ray(x1, y1, x, y, cub);
		// double ray_d = cub->p->perp_wall_dist;
		draw_game(i, ray_d, cub);
		// printf("ray_dist = %f\n", ray_d);
		i += 1;
		dir += dir_inc;
	}
	return (1);
}



//TODO redo raytrace to be able to cast more rays.