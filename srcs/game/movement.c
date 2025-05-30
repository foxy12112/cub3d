/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:35:15 by ldick             #+#    #+#             */
/*   Updated: 2025/05/30 19:02:04 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse(t_cub_data *cub)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cub->mlx, &mouse_x, &mouse_y);
	if (mouse_x > WIDHT / 2)
		rotate(cub, -1);
	if (mouse_x < WIDHT / 2)
		rotate(cub, 1);
	mlx_set_mouse_pos(cub->mlx, WIDHT / 2, HEIGHT / 2);
}

void	rotate(t_cub_data *cub, int direction)
{
	double	olddirx;
	double	oldplanex;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		direction = -1;
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		direction = 1;
	else if (direction == 0)
		return ;
	olddirx = cub->player_direction_x;
	oldplanex = cub->player_plane_x;
	cub->player_direction_x = cub->player_direction_x * cos(-ROT_SPEED
			* direction) - cub->player_direction_y * sin(-ROT_SPEED
			* direction);
	cub->player_direction_y = olddirx * sin(-ROT_SPEED * direction)
		+ cub->player_direction_y * cos(-ROT_SPEED * direction);
	cub->player_plane_x = cub->player_plane_x * cos(-ROT_SPEED * direction)
		- cub->player_plane_y * sin(-ROT_SPEED * direction);
	cub->player_plane_y = oldplanex * sin(-ROT_SPEED * direction)
		+ cub->player_plane_y * cos(-ROT_SPEED * direction);
}

void	movement_vertical(t_cub_data *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		if (is_valid_location(cub, cub->player_x + (cub->player_direction_x
					* SPEED), cub->player_y + (cub->player_direction_y
					* SPEED)))
		{
			cub->player_x += (cub->player_direction_x * SPEED);
			cub->player_y += (cub->player_direction_y * SPEED);
		}
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		if (is_valid_location(cub, cub->player_x + (cub->player_direction_x
					* -SPEED), cub->player_y + (cub->player_direction_y
					* -SPEED)))
		{
			cub->player_x += (cub->player_direction_x * -SPEED);
			cub->player_y += (cub->player_direction_y * -SPEED);
		}
	}
}

void	movement(t_cub_data *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		if (is_valid_location(cub, cub->player_x + (cub->player_direction_y
					* SPEED), cub->player_y - (cub->player_direction_x
					* SPEED)))
		{
			cub->player_x += (cub->player_direction_y * SPEED);
			cub->player_y -= (cub->player_direction_x * SPEED);
		}
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		if (is_valid_location(cub, cub->player_x - (cub->player_direction_y
					* SPEED), cub->player_y + (cub->player_direction_x
					* SPEED)))
		{
			cub->player_x -= (cub->player_direction_y * SPEED);
			cub->player_y += (cub->player_direction_x * SPEED);
		}
	}
}
