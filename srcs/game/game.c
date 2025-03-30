/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/03/30 14:57:00 by ldick            ###   ########.fr       */
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

static void	print_location_in_file(t_cub_data *cub) //TODO delete; illegal function
{
	FILE *file = fopen("logfile.txt", "a");
	int i = 0;
	while(i < 5)
	{
		// fprintf(file, "x[%d]=%d----y[%d]=%d----true_player_x=%d----true_player_y=%d\n", i, cub->move->x[i], i, cub->move->y[i], cub->minimap->p_img->instances[0].x - 50, cub->minimap->p_img->instances[0].y - 50);
		fprintf(file, "%d-%d-%d-%d-", cub->move->x[i], cub->move->y[i], cub->minimap->p_img->instances[0].x - 50, cub->minimap->p_img->instances[0].y - 50);
		i++;
	}
}

static double	correct_dir(double angle)
{
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle *= -1;
	return (angle);
}

void	movement(t_cub_data *cub)
{
	static int	i;
	double angle;
	double dir;
	
	dir = cub->p->dir;
	angle = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) && !collision(cub))
	{
		print_location_in_file(cub);
		if (cub->calculated != 1)
		{
			angle = dir * (M_PI / 180);
			calc_location(cub, angle);
			cub->calculated = 1;
		}
		printf("%f\n", dir);
		if (cub->move->x[i] < 0 || cub->move->y[i] < 0)
			return ;
		cub->minimap->p_img->instances[0].y = (cub->move->y[i] += 45);
		cub->minimap->p_img->instances[0].x = (cub->move->x[i] += 45);
		i++;
	}
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_S) && !collision(cub))
	{ 
		print_location_in_file(cub);
		if (cub->calculated != 2)
		{
			dir = correct_dir(dir + 180);
			angle = dir * (M_PI / 180);
			calc_location(cub, angle);
			cub->calculated = 2;
		}
		printf("%f\n", dir);
		if (cub->move->x[i] < 0 || cub->move->y[i] < 0)
			return ;
		cub->minimap->p_img->instances[0].y = (cub->move->y[i] += 45);
		cub->minimap->p_img->instances[0].x = (cub->move->x[i] += 45);
		i++;
	}
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_A) && !collision(cub))
	{
		if (cub->calculated != 3)
		{
			dir = correct_dir(dir - 90);
			angle = dir * (M_PI / 180);
			calc_location(cub, angle);
			cub->calculated = 3;
		}
		if (cub->move->x[i] < 0 || cub->move->y[i] < 0)
		return ;
		cub->minimap->p_img->instances[0].y = (cub->move->y[i] += 45);
		cub->minimap->p_img->instances[0].x = (cub->move->x[i] += 45);
		i++;
	}
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_D) && !collision(cub))
	{
		if (cub->calculated != 4)
		{
			dir = correct_dir(dir + 90);
			angle = dir * (M_PI / 180);
			calc_location(cub, angle);
			cub->calculated = 4;
		}
		if (cub->move->x[i] < 0 || cub->move->y[i] < 0)
			return ;
		cub->minimap->p_img->instances[0].y = (cub->move->y[i] += 45);
		cub->minimap->p_img->instances[0].x = (cub->move->x[i] += 45);
		i++;
	}
	// printf("angle = %f--cos angle = %f--sin angle = %f--dir = %f\n", angle, cos(angle), sin(angle), cub->p->dir);
	// if (collision(cub))
	// 	tp_back(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		cub->p->dir -= ROT_SPEED;
		cub->calculated = 0;
		i = 0;
	}
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->p->dir += ROT_SPEED;
		cub->calculated = 0;
		i = 0;
	}
	if (i > (int)LENGTH / 2)
	{
		cub->calculated = 0;
		i = 0;
	}
	if (cub->p->dir > 360)
		cub->p->dir = 0;
	if (cub->p->dir < 0)
		cub->p->dir = 360;
}

void ft_hook(void* param)
{
	t_cub_data* cub = (t_cub_data*)param;

	movement(cub);
	cub->p->x = (double)(cub->minimap->p_img->instances[0].x - 50) / (double)22;
	cub->p->y = (double)(cub->minimap->p_img->instances[0].y - 50) / (double)22;

	raytrace(cub);
	// printf("Actual position: (%.2f, %.2f)\n", cub->p->x, cub->p->y);
	// draw_ray(cub);
	// printf("%.5f\n", cub->p->dir);
}

void	game_loop(t_cub_data *cub)
{
	cub->ceiling = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 255);
	cub->floor = get_color(cub->texture->floor->r, cub->texture->floor->g, cub->texture->floor->b, 255);
	cub->img = mlx_new_image(cub->mlx, cub->mlx->width, cub->mlx->height);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	cub->img->instances->z = 0;
	draw_c_f(cub);
	map(cub);
	draw_player(cub);
	mlx_key_hook(cub->mlx, event, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}
