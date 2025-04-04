/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:32:50 by ldick             #+#    #+#             */
/*   Updated: 2025/04/04 19:10:11 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "main-libs/libs.h"

typedef struct	s_3d
{
	int			x;
	int			y;
	int			z;
	int			color_val;
}				t_3d;

typedef struct	s_fdf
{
	char		**map;
	t_3d		**three_d;
}				t_fdf;

int	check_for_comma(char *line)
{
	for (int i = 0; line[i]; i++)
		if (line[i] == ',')
			return (1);
	return (0);
}

t_3d *special_split(t_3d *fdf, char *line, int row)
{
	char **split = ft_split(line, ' ');
	int i = 0;
	while(split[i])
	{
		if(check_for_comma(split[i]) == 1)
		{
			char **diff_split = ft_split(split[i], ',');
			fdf[i].x = i;
			fdf[i].y = row;
			fdf[i].z = atoi(diff_split[0]);
			fdf[i].color_val = atoi(diff_split[1]);
			free(diff_split[0]);
			free(diff_split[1]);
			free(diff_split);
		}
		else if (check_for_comma(split[i]) == 0)
		{
			fdf[i].x = i;
			fdf[i].y = row;
			fdf[i].z = atoi(split[i]);
			fdf[i].color_val = 0xff0000ff;
		}
		free(split[i]);
	}
	free(split);
	free(line);
}

void	print(t_3d **three_d, int row)
{
	FILE *file = fopen("fdf_log.txt", "w");
	int i = 0;
	int j = 0;
	while(three_d[i])
	{
		while(three_d[i][j])
		{
			
		}
		fprintf(file, "%d, %d")
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	t_fdf *fdf = malloc(sizeof(fdf));
	int fd = open(argv[1], O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	while(!line)
	{
		fdf->three_d[i] = malloc(sizeof(t_3d));
		if (!fdf->three_d[i])
			return (0);
		
		fdf->three_d[i] = special_split(fdf, line, i);
		line = get_next_line(fd);
	}
	free(line);
	print(fdf->three_d);
}