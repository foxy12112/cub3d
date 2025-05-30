/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:07:25 by ldick             #+#    #+#             */
/*   Updated: 2025/05/30 16:54:02 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(t_cub_data *cub)
{
	if (!add_textures(cub))
		return (0);
	if (!add_map(cub))
		return (0);
	correct_map(cub);
	if (!add_player(cub))
		return (0);
	return (1);
}
