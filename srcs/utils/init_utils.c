/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foxy <foxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:16:37 by ldick             #+#    #+#             */
/*   Updated: 2025/01/23 19:22:08 by foxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*rm_s(char *str)
{
	int		i;
	int		j;
	int		lenght;

	lenght = ft_strlen(str);
	i = 0;
	j = 0;
	while(i < lenght)
	{
		if (str[i] != ' ')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

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
	else if (ft_strncmp(line, "F", 1) == 0)
		texture->floor = ft_strdup(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		texture->ceiling = ft_strdup(line + 1);
	else if ((line)[0] == '\n')
		return (i);
	else
		return (ft_error(), 720);
	return (i + 1);
}