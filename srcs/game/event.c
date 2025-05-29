/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:09 by ldick             #+#    #+#             */
/*   Updated: 2025/05/29 16:07:48 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_cub_data *cub)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub->player_direction_x;
	oldplanex = cub->player_plane_x;
	cub->player_direction_x = cub->player_direction_x * cos(ROT_SPEED) - cub->player_direction_y * sin(ROT_SPEED);
	cub->player_direction_y = olddirx * sin(ROT_SPEED) + cub->player_direction_y * cos(ROT_SPEED);
	cub->player_plane_x = cub->player_plane_x * cos(ROT_SPEED) - cub->player_plane_y * sin(ROT_SPEED);
	cub->player_plane_y = oldplanex * sin(ROT_SPEED) + cub->player_plane_y * cos(ROT_SPEED);
}

void	rotate_left(t_cub_data *cub)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub->player_direction_x;
	oldplanex = cub->player_plane_x;
	cub->player_direction_x = cub->player_direction_x * cos(-ROT_SPEED) - cub->player_direction_y * sin(-ROT_SPEED);
	cub->player_direction_y = olddirx * sin(-ROT_SPEED) + cub->player_direction_y * cos(-ROT_SPEED);
	cub->player_plane_x = cub->player_plane_x * cos(-ROT_SPEED) - cub->player_plane_y * sin(-ROT_SPEED);
	cub->player_plane_y = oldplanex * sin(-ROT_SPEED) + cub->player_plane_y * cos(-ROT_SPEED);
}

void	rotate(t_cub_data *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotate_right(cub);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		rotate_left(cub);
}

void	movement(t_cub_data *cub)
{
	double	move_speed;

	move_speed = SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		if (is_valid_location(cub, move_speed, cub->player_x + (cub->player_direction_x * move_speed), cub->player_y + (cub->player_direction_y * move_speed)))
		{
			cub->player_x += (cub->player_direction_x * move_speed);
			cub->player_y += (cub->player_direction_y * move_speed);
		}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		if (is_valid_location(cub, move_speed, cub->player_x + (cub->player_direction_x * -move_speed), cub->player_y + (cub->player_direction_y * -move_speed)))
		{
			cub->player_x += (cub->player_direction_x * -move_speed);
			cub->player_y += (cub->player_direction_y * -move_speed);
		}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		if (is_valid_location(cub, move_speed, cub->player_x + (cub->player_direction_y * move_speed), cub->player_y - (cub->player_direction_x * move_speed)))
		{
			cub->player_x += (cub->player_direction_y * move_speed);
			cub->player_y -= (cub->player_direction_x * move_speed);
		}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		if (is_valid_location(cub, move_speed, cub->player_x - (cub->player_direction_y * move_speed), cub->player_y + (cub->player_direction_x * move_speed)))
		{
			cub->player_x -= (cub->player_direction_y * move_speed);
			cub->player_y += (cub->player_direction_x * move_speed);
		}
}

void	draw_wall(t_cub_data *cub, int x, int y, int rec_size)
{
	int	i;

	i = 0;
	while(i < rec_size)
	{
		mlx_put_pixel(cub->img, (x + 1) * (rec_size + 2) - 2, y * (rec_size + 2) + i, 0x545454fa);
		mlx_put_pixel(cub->img, (x + 1) * (rec_size + 2) - 1, y * (rec_size + 2) + i, 0x545454fa);
		i++;
	}
	i = 0;
	while(i < rec_size)
	{
		mlx_put_pixel(cub->img, x * (rec_size + 2) + i, (y + 1) * (rec_size + 2) - 2, 0x545454fa);
		mlx_put_pixel(cub->img, x * (rec_size + 2) + i, (y + 1) * (rec_size + 2) - 1, 0x545454fa);
		i++;
	}
}

void	draw_square(t_cub_data *cub, int wall, int x, int y, int rec_size)
{
	int			color;
	// static int	x_true;
	// static int	y_true;
	int			i;
	int			j;

	j = 0;
	i = 0;
	color = wall ? 0xb56641ff : 0x747878ff;
	draw_wall(cub, x, y, rec_size);
	while(i < rec_size)
	{
		while(j < rec_size)
		{
			mlx_put_pixel(cub->img, x * (rec_size + 2) + i, y * (rec_size + 2) + j, color);
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
	while(cub->map[y])
	{
		while(cub->map[y][x])
		{
			if (cub->map[y][x] == '1'|| cub->map[y][x] == ' ')
				draw_square(cub, 1, x, y, /*calculate scale first*/ RECTANGLE);
			else
				draw_square(cub, 0, x, y, /*calculate scale first*/ RECTANGLE);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_player(t_cub_data *cub)
{
	// int	x;
	// int	y;

	// y = 0;
	// x = 0;
	// while(y <= 5)
	// {
	// 	while(x <= 5)
	// 	{
	// 		mlx_put_pixel(cub->img, cub->player_x * 22 + x, cub->player_y * 22 + y, 0xcbc3e3ff);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	mlx_put_pixel(cub->img, cub->player_x * 22, cub->player_y * 22, 0xcbc3e3ff);
}

void	mouse(t_cub_data *cub)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cub->mlx, &mouse_x, &mouse_y);
	if (mouse_x > WIDHT / 2)
		rotate_right(cub);
	if (mouse_x < WIDHT / 2)
		rotate_left(cub);
	mlx_set_mouse_pos(cub->mlx, WIDHT / 2, HEIGHT / 2);
}

void	exit_game(t_cub_data *cub)
{
	free_split(cub->map);
	free(cub->map);
	mlx_delete_texture(cub->texture_north);
	mlx_delete_texture(cub->texture_south);
	mlx_delete_texture(cub->texture_east);
	mlx_delete_texture(cub->texture_west);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_delete_image(cub->mlx, cub->omg);
	mlx_terminate(cub->mlx);
	free(cub);
	exit(0);
}

void	events(void *param)
{
	t_cub_data *cub;

	cub = (t_cub_data *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		exit_game(cub);
	movement(cub);
	rotate(cub);
	mouse(cub);
	draw_background(cub);
	dda_loop(cub);
	draw_map(cub);
	draw_player(cub);
	// printf("%f\t%f\t%f\t%f\n", cub->player_direction_x, cub->player_direction_y, cub->player_plane_x, cub->player_plane_y);
	// draw_map(cub);
}
