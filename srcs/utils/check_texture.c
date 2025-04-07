/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:18:14 by petrasostar       #+#    #+#             */
/*   Updated: 2025/04/07 11:34:53 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	check_texture(const char *path, const char *texture_name)
// {
// 	const char	*ext;

// 	if (!path || ft_strlen(path) == 0)
// 	{
// 		ft_error(NULL, "Error: Texture path is NULL");
// 		return (1);
// 	}
// 	if (access(path, F_OK) == -1)
// 	{
// 		ft_error(NULL, "Error: Texture file not found: ");
// 		ft_error(NULL, texture_name);
// 		return (1);
// 	}
// 	ext = strrchr(path, '.');
// 	if (!ext || strcmp(ext, ".png") != 0)
// 	{
// 		ft_error(NULL, "Error: Invalid texture format: ");
// 		ft_error(NULL, texture_name);
// 		return (1);
// 	}
// 	return (0);
// }
