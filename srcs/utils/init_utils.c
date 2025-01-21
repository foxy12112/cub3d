/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:16:37 by ldick             #+#    #+#             */
/*   Updated: 2025/01/20 19:25:04 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_texture(int i, t_texture_data *texture, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		texture->no = ft_strdup(line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		texture->so = ft_strdup(line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		texture->we = ft_strdup(line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		texture->ea = ft_strdup(line + 2);
	else
		return (i);
	return (i + 1);
}
