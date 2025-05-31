/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:07:25 by ldick             #+#    #+#             */
/*   Updated: 2025/05/31 14:34:36 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(t_cub_data *cub)
{
	if (!add_textures(cub))
		return (0);
	if (!add_map(cub))
		return (0);
	if (!add_player(cub))
		return (0);
	correct_map(cub);
	return (1);
}
