/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:38:51 by ldick             #+#    #+#             */
/*   Updated: 2025/01/19 18:55:16 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	initialize(char *argv[], t_cub_data *cub)
// {
// 	int		fd;
// 	char	*line;

// 	(void)cub;
// 	fd = open(argv[1], O_RDONLY);
// 	line = "0";
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (1);
// }

int	parsing(char *argv[], t_cub_data *cub)
{
	int		fd;
	char	*line;
	
	(void)cub;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (ft_strncmp(line, "NO", 2) == 0)
		cub->texture->no = ft_strdup(line + 2);
	if (ft_strncmp(line, "NO", 2) == 0)
		cub->texture->no = ft_strdup(line + 2);
	if (ft_strncmp(line, "NO", 2) == 0)
		cub->texture->no = ft_strdup(line + 2);
	if (ft_strncmp(line, "NO", 2) == 0)
		cub->texture->no = ft_strdup(line + 2);
	printf("%s\n", cub->texture->no);
	return(1);

}
