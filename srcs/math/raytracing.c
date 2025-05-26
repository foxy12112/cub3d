/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:29:42 by ldick             #+#    #+#             */
/*   Updated: 2025/05/25 15:25:06 by ldick            ###   ########.fr       */
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
		// if (cub->side_dist_x)
		i++;
	}
	if (dx > dy)
		cub->side = 0;
	else
		cub->side = 1;
	cub->hit_x = x0;
	cub->hit_y = y0;
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
	// cub->hit_x = (x0 - 50) / 22;
	// cub->hit_y = (y0 - 50) / 22;
	cub->hit_x = x0;
	cub->hit_y = y0;
	if (dx > dy)
		cub->side = 0;
	else
		cub->side = 1;
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


// void	draw_v_line(int x, int start, int end, t_cub_data *cub, int old, int oldy)
// {
// 	int color = 0xff0000ff;
// 	if (old = cub->map_x && oldy == cub->map_y)
// 		color = 0xffff00ff;
// 	while(start++ < end)
// 	{
// 		mlx_put_pixel(cub->img, x, start, color);
// 	}
// }

// void	texturize(t_cub_data *cub, int x, int start, int end, int line_height, mlx_texture_t *tex, double ray_d, t_raycasting ray_data)
// {
// 	int	tex_y;
// 	double	step;
// 	double	tex_pos;
// 	int		ind;
// 	int		y;
// 	double	wall_x;
// 	int		tex_x;

// 	y = start;
// 	// if (cub->side == 1)
// 	// 	wall_x = cub->p->x + ray_d * cub->ray_dir_x;
// 	// else
// 	// 	wall_x = cub->p->y + ray_d * cub->ray_dir_y;
// 	if (cub->side == 0)
// 		wall_x = cub->p->y + ray_d * ray_data.ray_dir_y;
// 	else
// 		wall_x = cub->p->x + ray_d * ray_data.ray_dir_x;
// 	// printf("%f\n", cub->ray_dir_y);
// 	// wall_x /= 29;
// 	wall_x -= floor(wall_x);
// 	// wall_x = cub->hit_x;
// 	tex_x = (int)(wall_x * tex->width);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= tex->width)
// 		tex_x = tex->width - 1;
// 	// if (cub->side == 0 && cub->ray_dir_x > 0)
// 	// 	tex_x = tex->width - tex_x - 1;
// 	// if (cub->side == 1 && cub->ray_dir_y < 0)
// 	// 	tex_x = tex->width - tex_x - 1;
// 	step = (double)tex->height / (double)line_height;
// 	tex_pos = (start - HEIGHT / 2 + line_height / 2) * step;
// 	while(y <= end)
// 	{
// 		tex_y = (int)tex_pos % tex->height;
// 		if (tex_y < 0)
// 			tex_y += tex->height;
// 		uint32_t color = get_pixel_color(&(tex->pixels[(tex_y * tex->width + tex_x) * 4]));
// 		mlx_put_pixel(cub->img, x, y, color);
// 		tex_pos += step;
// 		y++;
// 	}
// }

void	texturize(t_cub_data *cub, int x, int start, int end, int line_height, mlx_texture_t *tex, double ray_d)
{
	int	tex_y;
	double	step;
	double	tex_pos;
	int		ind;
	int		y;
	double	wall_x;
	int		tex_x;

	step = 1.0 * (double)tex->height / (double)line_height;
	tex_pos = (start - HEIGHT / 2 + line_height / 2) * step;
	y = start;
	if (cub->side == 0)
		wall_x = cub->p->y + ray_d * cub->ray_dir_y;
	else
		wall_x = cub->p->x + ray_d * cub->ray_dir_x;
	wall_x /= 28;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (cub->side == 0 && cub->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (cub->side == 1 && cub->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	int dy = tex->height;
	int dx = line_height;
	int err = dx / 2;
	while(y <= end)
	{
		tex_y = (int)tex_pos % tex->height;
		if (tex_y < 0)
			tex_y += tex->height;
		uint32_t color = get_pixel_color(&(tex->pixels[(tex_y * tex->width + tex_x) * 4]));
		mlx_put_pixel(cub->img, x, y, color);
		tex_pos += step;
		y++;
	}
}

int	is_out_of_bound(char **map, int x, int y)
{
	if ((y - 50) / 22 < 0 || (x - 50) / 22)
		return (1);
	if (!map[(y - 50) / 22])
		return (1);
	if (!map[(y - 50) / 22][(x - 50) / 22])
		return (1);
	return (0);
}

// mlx_texture_t	*get_correct_texture(t_cub_data *cub, int hit_x, int hit_y)
// {
// 	if (cub->map[hit_y][hit_x] == '1')
// 	{
// 		if (!is_out_of_bound(cub->map, hit_x, hit_y + 1))
// 		{
// 			if (cub->map[cub->hit_y + 1][cub->hit_x] == '0')
// 				return (cub->texture->no_tex);
// 		}
// 		if (!is_out_of_bound(cub->map, cub->hit_x, cub->hit_y - 1))
// 		{
// 			if (cub->map[cub->hit_y - 1][cub->hit_x] == '0')
// 				return (cub->texture->so_tex);
// 		}
// 		if (!is_out_of_bound(cub->map, cub->hit_x + 1, cub->hit_y))
// 		{
// 			if (cub->map[cub->hit_y][cub->hit_x + 1] == '0')
// 				return (cub->texture->ea_tex);
// 		}
// 		if (!is_out_of_bound(cub->map, cub->hit_x - 1, cub->hit_y))
// 		{
// 			if (cub->map[cub->hit_y][cub->hit_x - 1] == '0')
// 				return (cub->texture->we_tex);
// 		}
// 	}
// 	return (cub->texture->missing_texture);
// }	//TODO make a check for if multiple textures share the same wall

// mlx_texture_t	*get_correct_texture_based_on_hit_position(t_cub_data *cub)
// {
// 	int	return_value;

// 	return_value = 0;
// 	if (cub->map[(cub->hit_y - 50) / 22][(cub->hit_x - 50) / 22] == '1')
// 	{
// 			if (cub->hit_y > round(cub->p->y))
// 				return_value = 1;
// 			else if (cub->hit_y < round(cub->p->y))
// 				return_value = 2;
// 			if (cub->hit_x > round(cub->p->x))
// 				return_value = 3;
// 			else if (cub->hit_x < round(cub->p->x))
// 				return_value = 4;
// 	}
// 	if (return_value == 1)
// 		return (cub->texture->so_tex);
// 	if (return_value == 2)
// 		return (cub->texture->no_tex);
// 	if (return_value == 3)
// 		return (cub->texture->ea_tex);
// 	if (return_value == 4)
// 		return (cub->texture->we_tex);
// 	return (cub->texture->missing_texture);
// }

void	draw_game(int x, double ray_d, t_cub_data *cub, int oldx, int oldy, double ray_dir_x)
{
	double line_hight = ((32 / ray_d) * (WIDHT / 2)) + (cub->mlx->height / cub->p->perp_wall_dist); 
	if (line_hight >= cub->mlx->height)
		line_hight = cub->mlx->height;
	if (line_hight <= 20)
		line_hight = 20;
	int	draw_start = (HEIGHT - line_hight) / 2;
	int draw_end = (draw_start + line_hight);
	if (draw_end >= cub->mlx->height)
		draw_end = cub->mlx->height - 1;
	mlx_texture_t * texture;
	if (((cub->hit_x - 50) / 22) % 2 == 0 && (cub->hit_y - 50) / 22 % 2 == 0)
		texture = cub->texture->no_tex;
	else
		texture = cub->texture->so_tex;
	// texturize(cub, x, draw_start, draw_end, line_hight, get_wall_texture(cub), ray_d); //TODO
	texturize(cub, x, draw_start, draw_end, line_hight, texture, ray_d); //TODO
}

// void	draw_game(t_raycasting ray_data, t_cub_data *cub)
// {
// 	double	line_height;
// 	int		draw_start;
// 	int		draw_end;

// 	// line_height = HEIGHT / ray_data.perp_wall_dist;
// 	line_height = ((32 / ray_data.perp_wall_dist) * (WIDHT / 2)) + (cub->mlx->height / cub->p->perp_wall_dist);
// 	if (line_height >= HEIGHT)
// 		line_height = HEIGHT;
// 	if (line_height <= 20)
// 		line_height = 20;
// 	printf("%f\n", ray_data.perp_wall_dist);
// 	draw_start = -line_height / 2 + HEIGHT / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = line_height / 2 + HEIGHT / 2;
// 	if (draw_end >= HEIGHT)
// 		draw_end = HEIGHT - 1;
// 	printf("%f\t%d\t%d\n", line_height, draw_start, draw_end);
// 	texturize(cub, ray_data.counter, draw_start, draw_end, line_height, cub->texture->ea_tex, ray_data.perp_wall_dist, ray_data);
// }

// void	save_location_until_new_wall(t_cub_data *cub)
// {
// 	static int x;
// 	static int y;

// 	if ()
// }




int	raytrace(t_cub_data *cub)
{
	double x1;
	double y1;
	double x;
	double y;
	double angle;
	double	i;
	double cameraX, ray_dir_x, ray_dir_y;
	i = 0;
	draw_c_f(cub);
	double dir_inc = (double)FOV * (M_PI / 180.0) / (double)1920;
	double dir_x = cub->p->dir_x;
	double dir_y = cub->p->dir_y;
	double fov_rad = (double)FOV * (M_PI / 180.0);
	double half_fov = fov_rad / 2.0;
	double old_dir_x = dir_x;
	dir_x = dir_x * cos(-half_fov) - dir_y * sin(-half_fov);
	dir_y = old_dir_x * sin(-half_fov) + dir_y * cos(-half_fov);
	double	view_angle = atan2(cub->p->dir_y, cub->p->dir_x);
	double ray_angle;
	double plane_mag = tan(fov_rad / 2.0);
	while(i < 1920)
	{
		x1 = cub->p->x;
		y1 = cub->p->y;
		double olddirx = dir_x;
		double camera_x = 2 * i / 1920.0 - 1;
		cub->ray_dir_x = cub->p->dir_x + cub->p->plane_x * camera_x;
		cub->ray_dir_y = cub->p->dir_y + cub->p->plane_y * camera_x;
		x = x1 + (dir_x * cub->mlx->width);
		y = y1 + (dir_y * cub->mlx->width);
		// x = x1 + (cub->ray_dir_x * cub->mlx->width);
		// y = y1 + (cub->ray_dir_y * cub->mlx->width);
		int oldmapx, oldmapy;
		oldmapx = cub->map_x;
		oldmapy = cub->map_y;
		double ray_d = ray(x1, y1, x, y, cub);
		cub->p->plane_x = -cub->p->dir_y * plane_mag;
		cub->p->plane_y = cub->p->dir_x * plane_mag;
		ray_angle = atan2(cub->ray_dir_y, cub->ray_dir_x);
		ray_d = ray_d * cos(ray_angle - view_angle);
		draw_game(i, ray_d, cub, oldmapx, oldmapy, ray_dir_x);
		i += 1;
		// save_location_until_new_wall(cub, );
		dir_x = dir_x * cos(dir_inc) - dir_y * sin(dir_inc);
		dir_y = olddirx * sin(dir_inc) + dir_y * cos(dir_inc); //TODO 
	}
	return (1);
}


// int	raytrace(t_cub_data *cub)
// {
// 	t_raycasting	ray_data;
	
// 	ray_data.counter = 0;
// 	ray_data.camera_x = 2 * ray_data.counter / (double)WIDHT - 1;
// 	ray_data.increment.fov_rad = (double)FOV * (M_PI / 180);
// 	ray_data.increment.half_fov = ray_data.increment.fov_rad / 2.0;
// 	ray_data.increment.dir_inc = ray_data.increment.fov_rad / (double)WIDHT;
// 	ray_data.increment.dir_x = cub->p->dir_x * cos(-ray_data.increment.half_fov) - cub->p->dir_y * sin(-ray_data.increment.half_fov);
// 	ray_data.increment.dir_y = cub->p->dir_x * sin(-ray_data.increment.half_fov) + cub->p->dir_y * cos(-ray_data.increment.half_fov);
// 	ray_data.increment.view_angle = atan2(cub->p->dir_y, cub->p->dir_x);
// 	while(ray_data.counter < WIDHT)
// 	{
// 		ray_data.position.x = cub->p->x;
// 		ray_data.position.y = cub->p->y;
// 		ray_data.ray_dir_x = cub->p->dir_x + cub->p->plane_x * ray_data.camera_x;
// 		ray_data.ray_dir_y = cub->p->dir_y + cub->p->plane_y * ray_data.camera_x;
// 		ray_data.position1.x = ray_data.position.x + (ray_data.increment.dir_x * WIDHT);
// 		ray_data.position1.y = ray_data.position.y + (ray_data.increment.dir_y * WIDHT);
// 		ray_data.ray_distance = ray(ray_data.position.x, ray_data.position.y, ray_data.position1.x, ray_data.position1.y, cub);
// 		cub->p->plane_x = -cub->p->dir_y * ray_data.increment.plane_mag;
// 		cub->p->plane_y = cub->p->dir_y * ray_data.increment.plane_mag;
// 		ray_data.ray_angle = atan2(ray_data.ray_dir_x, ray_data.ray_dir_y);
// 		ray_data.perp_wall_dist = ray_data.ray_distance * cos(ray_data.ray_angle - ray_data.increment.view_angle);
// 		draw_game(ray_data, cub);
// 		ray_data.counter++;
// 		ray_data.increment.dir_x = ray_data.increment.dir_x * cos(ray_data.increment.dir_inc) - ray_data.increment.dir_y * sin(ray_data.increment.dir_inc);
// 		ray_data.increment.dir_y = ray_data.increment.old_dir_x * sin(ray_data.increment.dir_inc) - ray_data.increment.dir_y * cos(ray_data.increment.dir_inc);
// 	}
// 	return (1);
// }

// int	ft_temp_abs(int *value)
// {
// 	if (*value < 0)
// 		*value = -*value;
// }

// static t_raycasting	ray_x(t_raycasting ray, t_cub_data *cub)
// {
// 	t_calculations calc;

// 	calc.dx = ray.position1.x - ray.position.x;
// 	calc.dy = ray.position1.y - ray.position.y;
// 	if (calc.dx > 0)
// 		calc.step_x = 2;
// 	else
// 		calc.dx = -2;
// 	if (calc.dy > 0)
// 		calc.step_y = 2;
// 	else
// 		calc.step_y = -2;
// 	ft_temp_abs(&calc.dx);
// 	ft_temp_abs(&calc.dy);
// 	calc.start_x = ray.position.x;
// 	calc.start_y = ray.position.y;
// 	calc.counter = 0;
// 	calc.decision = (2 * calc.dy) - calc.dx;
// 	while (calc.counter <= calc.dx && !touch(ray.position.x - 50, ray.position.y - 50, cub))
// 	{
// 		if (calc.decision >= 0)
// 		{
// 			ray.position.y += calc.step_y;
// 			calc.decision -= 2 * calc.dx;
// 		}
// 		else
// 		{
// 			ray.position.x += calc.step_x;
// 			calc.decision += 2 * calc.dx;
// 		}
// 		if ()
// 	}
// }
