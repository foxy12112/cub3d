/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:28:25 by ldick             #+#    #+#             */
/*   Updated: 2025/06/02 13:23:30 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	correct_map(t_cub_data *cub)
{
	char	*newline;
	int		y;

	y = 0;
	while (cub->map[y])
	{
		newline = ft_strchr(cub->map[y], '\n');
		if (newline)
			*newline = '\0';
		y++;
	}
	cub->map[(int)cub->player_start_y][(int)cub->player_start_x] = '0';
}

int	check_closed(t_cub_data *cub)
{
	int	x;
	int	y;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (ft_strchr("0NSWE", cub->map[y][x]))
			{
				if (y == 0 || x == 0)
					return (printf("Error\ntop or left not closed\n"), 0);
				if (!cub->map[y + 1])
					return (printf("Error\nbotom not closed\n"), 0);
				if (!cub->map[y][x + 1])
					return (printf("Error\nright side not closed\n"), 0);
				if (!cub->map[y + 1][x] || !cub->map[y - 1][x])
					return (printf("Error\noverhang not closed\n"), 0);
				if (!cub->map[y][x - 1])
					return (printf("Error\nOverhang? not closed\n"), 0);
			}
		}
	}
	return (1);
}

int	validate(t_cub_data *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (cub->map[y])
	{
		while (cub->map[y][x])
		{
			if (!ft_strchr("01 NESW", cub->map[y][x]))
				return (printf("Error\nillegal character in map\n"), 0);
			x++;
		}
		x = 0;
		y++;
	}
	if (!check_closed(cub) || !validate_textures(cub))
		return (0);
	return (1);
}

int	validate_textures(t_cub_data *cub)
{
	if (!cub->texture_east || !cub->texture_north || !cub->texture_south
		|| !cub->texture_west || !cub->ceiling || !cub->floor)
		return (printf("Error\ntexture validation failed\n"), 0);
	return (1);
}
