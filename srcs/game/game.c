/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/04/24 17:45:42 by ldick            ###   ########.fr       */
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

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	rotate(t_cub_data *cub)
{
	double	olddirx;
	double	oldplanex;
	double	rotation_angle;
	int		dir;
	double	angle;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		dir = 1;
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		dir = -1;
	else
		return ;
	rotation_angle = dir * ROT_SPEED;
	angle += dir * (ROT_SPEED * 180 / M_PI);
	olddirx = cub->p->dir_x;
	cub->p->dir_x = cub->p->dir_x * cos(rotation_angle) - cub->p->dir_y * sin(rotation_angle);
	cub->p->dir_y = olddirx * sin(rotation_angle) + cub->p->dir_y * cos(rotation_angle);
}

int	valid_location(int x, int y, t_cub_data *cub)
{
	if (cub->map == NULL || cub->map[y] == NULL || cub->map[y][x] == NULL)
		return (0);
	if (cub->map[y][x] == '1' || cub->map[y][x] == ' ')
		return (0);
	return (1);
}

void	movement(t_cub_data *cub)
{
	double	new_x;
	double	new_y;
	int		move_speed;

	move_speed = SPEED;
	new_x = cub->p->x;
	new_y = cub->p->y;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT))
		move_speed = 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		new_x = cub->p->x +  (cub->p->dir_x * move_speed);
		new_y = cub->p->y + (cub->p->dir_y * move_speed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		new_x = cub->p->x + (cub->p->dir_x * -move_speed);
		new_y = cub->p->y + (cub->p->dir_y * -move_speed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		new_x = cub->p->x + cub->p->dir_y * move_speed;
		new_y = cub->p->y - cub->p->dir_x * move_speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		new_x = cub->p->x - (cub->p->dir_y * move_speed);
		new_y = cub->p->y + (cub->p->dir_x * move_speed);
	}
	if (valid_location((int)((new_x - 55) / 22), (int)((new_y - 55) / 22), cub))
	{
		cub->p->x = new_x;
		cub->minimap->p_img->instances->x = round(new_x);
		cub->p->y = new_y;
		cub->minimap->p_img->instances->y = round(new_y);
	}
	printf("%c\tx=%d\ty=%d\n", cub->map[(int)(new_y - 55) / 22][(int)(new_x - 55) / 22], (int)(round(new_x) - 55) / 22, (int)(round(new_y) - 55) / 22);
}

void	loop_hook(void *param)
{
	t_cub_data	*cub;
	double		turn_speed;

	cub = (t_cub_data *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) || mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotate(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_0))
		draw_ray(cub);
	// if (mlx_is_key_down)
	movement(cub);
	raytrace(cub);
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
	mlx_loop_hook(cub->mlx, &loop_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}