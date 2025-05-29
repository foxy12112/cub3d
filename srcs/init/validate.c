/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:28:25 by ldick             #+#    #+#             */
/*   Updated: 2025/05/29 16:07:00 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top(t_cub_data *cub)
{
	int	x;
	
	x = 0;
	while(cub->map[0][x])
	{
		if (!ft_strchr("1 ", cub->map[0][x]))
			return (printf("top not closed\n"), 0);
		x++;
	}
	return (1);
}

int	check_bottom(t_cub_data *cub)
{
	int	x;
	
	x = 0;
	while(cub->map[cub->map_height - 1][x])
	{
		if (!ft_strchr("1 ", cub->map[cub->map_height - 1][x]))
			return (printf("bottom not closed\n"), 0);
		x++;
	}
	return (1);
}

int	check_left(t_cub_data *cub)
{
	int	y;

	y = 0;
	while(cub->map[y])
	{
		if (!ft_strchr("1 ", cub->map[y][0]))
			return (printf("left side not closed\n"), 0);
		y++;
	}
	return (1);
}

int	check_right(t_cub_data *cub)
{
	int	y;

	y = 0;
	while(cub->map[y])
	{
		if (!ft_strchr("1 ", cub->map[y][ft_strlen(cub->map[y])]))
			return (printf("right side not closed\n"), 0);
		y++;
	}
	return (1);
}
int	check_closed(t_cub_data *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while(cub->map[y])
	{
		while(cub->map[y][x])
		{
			if (cub->map[y][x] == '0')
			{
				if (y == 0 || x == 0)
					return (printf("leaking frfr\n"), 0);
				if (!cub->map[y + 1])
					return (printf("leakign frfr\n"), 0);
				if (!cub->map[y][x + 1])
					return (printf("leaking frfrfr\n"), 0);
				if (!cub->map[y + 1][x])
					return (printf("leaking frfrfrfr\n"), 0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

int	validate(t_cub_data *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while(cub->map[y])
	{
		while(cub->map[y][x])
		{
			if (!ft_strchr("01 NESW", cub->map[y][x]))
				return(0);
			x++;
		}
		x = 0;
		y++;
	}
	if (!check_closed(cub))
		return (0);
	return (1);
}
