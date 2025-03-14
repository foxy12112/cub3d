/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:01:07 by ldick             #+#    #+#             */
/*   Updated: 2025/03/14 11:31:20 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	collision_top(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x;
	y = cub->p->y - 0.05;

	while(x <= cub->p->x + 0.56)
	{
		if (cub->map[(int)y][(int)x] == '1')
			return (true);
		x += 0.05;
	}
	return (false);
}

bool	collision_bottom(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x;
	y = cub->p->y - 0.05;

	while(x <= cub->p->x + 0.56)
	{
		if (cub->map[(int)(y + 0.65)][(int)x] == '1')
			return (true);
		x += 0.05;
	}
	return (false);
}

bool	collision_left(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x - 0.05;
	y = cub->p->y;

	while(y <= cub->p->y + (double)0.55)
	{
		if (cub->map[(int)y][(int)x] == '1')
			return (true);
		y += 0.05;
	}
	return (false);
}

bool	collision_right(t_cub_data *cub)
{
	double	x;
	double	y;

	x = cub->p->x - 0.05;
	y = cub->p->y;

	while(y <= cub->p->y + 0.56)
	{
		if (cub->map[(int)y][(int)(x + 0.65)] == '1')
			return (true);
		y += 0.05;
	}
	return (false);
}

// int	collision(t_cub_data *cub)
// {
// 	double	x;
// 	double	y;

// 	x = cub->p->x;
// 	y = cub->p->y;
// 	printf("%d--%d--%f--%f\n", (int)x, (int)y, x, y);
// 	printf("%c\n", cub->map[(int)(y - 0.6)][(int)x]);
// 	if (cub->map[(int)(y + 0.65)][(int)x] == '1')
// 		return (1);
// 	else if (cub->map[(int)(y - 0.05)][(int)x] == '1')
// 		return (2);
// 	if (cub->map[(int)y][(int)(x - 0.05)] == '1')
// 		return (3);
// 	else if (cub->map[(int)y][(int)(x - 0.65)] == '1')
// 		return (4);
// 	return (0);
// }

void	draw_play(t_cub_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i <= PSIZE)
	{
		while(j <= PSIZE)
		{
			mlx_put_pixel(cub->minimap->p_img, i, j, 0xff32c8ff);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_player(t_cub_data *cub)
{
	int	p_start_x;
	int	p_start_y;
	// 160, 240;
	p_start_x = (50 + (PSIZE / 2) +  (int)(cub->p->x) * cub->minimap->scale + (2 * cub->p->x));
	p_start_y = (50 + (PSIZE / 2) + (int)(cub->p->y) * cub->minimap->scale + (2 * cub->p->y));
	printf("p_start_x = %d, p_start_y = %d\n", p_start_x, p_start_y);
	cub->minimap->p_img = mlx_new_image(cub->mlx, 20, 20);
	mlx_image_to_window(cub->mlx, cub->minimap->p_img, p_start_x, p_start_y);
	printf("p_img_x = %d, p_img_y = %d\n", cub->minimap->p_img->instances[0].x, cub->minimap->p_img->instances[0].y);
	draw_play(cub);
	// cub->minimap->p_img;
	return ;
}


// void	rotate_player(t_cub_data *cub, mlx_key_data_t *mkd)
// {
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
// 	{
// 		cub->minimap->p_img->instances
// 	}
// 	else if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
// 	{
		
// 	}
// }