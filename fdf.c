/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:32:50 by ldick             #+#    #+#             */
/*   Updated: 2025/04/06 14:55:41 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "main-libs/libs.h"

#define MAX_WIDTH 100

typedef struct	s_3d
{
	int			x;
	int			y;
	int			z;
	int			color_val;
	int			size;
}				t_3d;

typedef struct	s_fdf
{
	char		**map;
	t_3d		**three_d;
}				t_fdf;

int	check_for_comma(char *line)
{
	printf("%s\n", line);
	for (int i = 0; line[i]; i++)
		if (line[i] == ',')
			return (1);
	return (0);
}

int	get_size(char **array)
{
	int count = 0;
	while(array && array[count])
		count++;
	return (count);
}

t_3d *special_split(t_3d *fdf, char *line, int row)
{
	char **split = ft_split(line, ' ');
	// printf("%s\n", line);
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
			fdf[i].size = get_size(split);
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
			fdf[i].size = get_size(split);
		}
		free(split[i]);
		i++;
		if (split[i] == NULL)
			break ;
	}
	free(split);
	return (fdf);
}


void	print(t_3d **three_d, int row)
{
	FILE *file = fopen("fdf_log.txt", "w");
	int i = 0;
	int j = 0;
	while(i < row)
	{
		while(three_d[i][j].size > j)
		{
			// printf("%d--j-%d\n", three_d[i][j].size, j);
			fprintf(file, "%d , %d\t", three_d[i][j].x, three_d[i][j].color_val);
			j++;
		}
		fprintf(file, "\n");
		i++;
		j = 0;
		// fprintf(file, "%d, %d")
	}
	fclose(file);
}

int get_rows(char *file)
{
	int fd = open(file, O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	return (i);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	remove("fdf_log.txt");
	int row = get_rows(argv[1]);
	t_fdf *fdf = malloc(sizeof(t_fdf));
	fdf->three_d = malloc(sizeof(t_3d) * row);
	for(int i = 0; i < row; i++)
		fdf->three_d[i] = malloc(sizeof(t_3d) * MAX_WIDTH);
	int fd = open(argv[1], O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	while(i < row && line)
	{
		fdf->three_d[i] = special_split(fdf->three_d[i], line, i);
		line = get_next_line(fd);
		i++;
	}
	print(fdf->three_d, row);
	// printf("atoi of hex number = %d", atoi("0xFFFFFF");)
	return (0);
}