/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:47:47 by ldick             #+#    #+#             */
/*   Updated: 2025/05/28 16:09:52 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *path)
{
	int	lenght;

	lenght = ft_strlen(path);
	printf("%c\t%c\t%c\t%c\n", path[lenght - 1], path[lenght - 2], path[lenght - 3], path[lenght - 4]);
	if (path[lenght - 1] != 'b' || path[lenght - 2] != 'u' || path[lenght - 3] != 'c' || path[lenght - 4] != '.')
		return (0);
	return(1);
	// printf("%c\n", path[lenght - 1]);
}