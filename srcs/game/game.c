/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:37:47 by ldick             #+#    #+#             */
/*   Updated: 2025/05/18 13:56:05 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_c_f(t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->mlx->height / 2)
	{
		while (j < cub->mlx->width)
		{
			mlx_put_pixel(cub->img, j, i, cub->ceiling);
			j++;
		}
		j = 0;
		i++;
	}
	while (i < cub->mlx->height)
	{
		while (j < cub->mlx->width)
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

void	rotate_right(t_cub_data *cub)
{
	double	olddirx;
	double	oldplanex;
	
	olddirx = cub->p->dir_x;
	oldplanex = cub->p->plane_x;
	cub->p->dir_x = cub->p->dir_x * cos(-ROT_SPEED) - cub->p->dir_y * sin(-ROT_SPEED);
	cub->p->dir_y = olddirx * sin(-ROT_SPEED) + cub->p->dir_y * cos(-ROT_SPEED);
	cub->p->plane_x = cub->p->plane_x * cos(-ROT_SPEED) - cub->p->plane_y * sin(-ROT_SPEED);
	cub->p->plane_y = oldplanex * sin(-ROT_SPEED) + cub->p->plane_y * cos(-ROT_SPEED);
}

void	rotate_left(t_cub_data *cub)
{
	double	olddirx;
	double	oldplanex;
	
	olddirx = cub->p->dir_x;
	oldplanex = cub->p->plane_x;
	cub->p->dir_x = cub->p->dir_x * cos(ROT_SPEED) - cub->p->dir_y * sin(ROT_SPEED);
	cub->p->dir_y = olddirx * sin(ROT_SPEED) + cub->p->dir_y * cos(ROT_SPEED);
	cub->p->plane_x = cub->p->plane_x * cos(ROT_SPEED) - cub->p->plane_y * sin(ROT_SPEED);
	cub->p->plane_y = oldplanex * sin(ROT_SPEED) + cub->p->plane_y * cos(ROT_SPEED);
}

void	rotate(t_cub_data *cub)
{
	double	olddirx;
	double	oldplanex;
	double	rotation_angle;
	int		dir;
	double	angle;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotate_right(cub);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		rotate_left(cub);
	else
		return ;
}

int	valid_location(int x, int y, t_cub_data *cub)
{
	int	x1;
	int	y1;
	x1 = (x - 50) / 22;
	y1 = (y - 50) / 22;
	if (cub->map == NULL || cub->map[y1] == NULL || cub->map[y1][x1] == NULL)
		return (0);
	if (cub->map[y1][x1] == '1' || cub->map[y1][x1] == ' ')
		return (0);
	x1 = (x - 50 + 10) / 22;
	y1 = (y - 50 + 10) / 22;
	if (cub->map[y1][x1] == '1' || cub->map[y1][x1] == ' ')
		return (0);
	x1 = (x - 50) / 22;
	if (cub->map[y1][x1] == '1' || cub->map[y1][x1] == ' ')
		return (0);
	x1 = (x - 50 + 10) / 22;
	y1 = (y - 50) / 22;
	if (cub->map[y1][x1] == '1' || cub->map[y1][x1] == ' ')
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
		if (valid_location(cub->p->x + (cub->p->dir_x * move_speed), cub->p->y + (cub->p->dir_y * move_speed), cub))
		{
			new_x = cub->p->x + (cub->p->dir_x * move_speed);
			new_y = cub->p->y + (cub->p->dir_y * move_speed);
		}
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		if (valid_location(cub->p->x + (cub->p->dir_x * -move_speed), cub->p->y + (cub->p->dir_y * -move_speed), cub))
		{
			new_x = cub->p->x + (cub->p->dir_x * -move_speed);
			new_y = cub->p->y + (cub->p->dir_y * -move_speed);
		}
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		if (valid_location(cub->p->x + cub->p->dir_y * move_speed, cub->p->y - cub->p->dir_x * move_speed, cub))
		{
			new_x = cub->p->x + cub->p->dir_y * move_speed;
			new_y = cub->p->y - cub->p->dir_x * move_speed;
		}
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		if (valid_location(cub->p->x - cub->p->dir_y * move_speed, cub->p->y + cub->p->dir_x * move_speed, cub))
		{
			new_x = cub->p->x - (cub->p->dir_y * move_speed);
			new_y = cub->p->y + (cub->p->dir_x * move_speed);
		}
	}
	cub->minimap->p_img->instances->x = round(new_x);
	cub->minimap->p_img->instances->y = round(new_y);
	// printf("%f\t%f\n", (new_x - 50) / 22, (new_y - 50) / 22);
	cub->p->y = new_y;
	cub->p->x = new_x;
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
	movement(cub);
	draw_c_f(cub);
	raycasting(cub);
	// texturize(cub);
	// raytrace(cub);
}

void	game_loop(t_cub_data *cub)
{
	cub->ceiling = get_color(cub->texture->ceiling->r, cub->texture->ceiling->g, cub->texture->ceiling->b, 255);
	cub->floor = get_color(cub->texture->floor->r, cub->texture->floor->g, cub->texture->floor->b, 255);
	cub->img = mlx_new_image(cub->mlx, cub->mlx->width, cub->mlx->height);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	cub->img->instances->z = 0;
	map(cub);
	draw_player(cub);
	mlx_loop_hook(cub->mlx, &loop_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}
