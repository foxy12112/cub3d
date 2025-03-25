/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:52:10 by petrasostar       #+#    #+#             */
/*   Updated: 2025/03/21 12:04:36 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_file(char *path, char *texture_name)
{
	if (!path)
	{
		ft_error(NULL, "Error: Texture path is NULL");
		return (1);
	}
	if (open(path, O_RDONLY) == -1)
	{
		ft_error(NULL, "Error opening texture: ");
		ft_error(NULL, texture_name);
		return (1);
	}
	return (0);
}

int	check_textures(t_cub_data *cub)
{
	if (!cub->texture)
	{
		ft_error(NULL, "Error: Texture struct is NULL");
		return (1);
	}
	if (check_texture_file(cub->texture->no, "North texture") == 1)
		return (1);
	if (check_texture_file(cub->texture->so, "South texture") == 1)
		return (1);
	if (check_texture_file(cub->texture->we, "West texture") == 1)
		return (1);
	if (check_texture_file(cub->texture->ea, "East texture") == 1)
		return (1);
	return (0);
}
