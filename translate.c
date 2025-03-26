/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:53:30 by ldick             #+#    #+#             */
/*   Updated: 2025/03/26 18:45:39 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main-libs/libs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

static int	count_lines(FILE *file)
{
	int		count;
	char	ch;

	if (file == NULL)
	{
		return (-1);
	}
	count = 0;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '-')
			count++;
	}
	rewind(file);
	return (count / 4);
}

void calculate_average_movement(int *x, int *y, int size, double *avg_direction, double *avg_distance) {
    if (size < 2) {
        *avg_direction = 0;
        *avg_distance = 0;
        return;
    }
    
    double total_direction = 0.0;
    double total_distance = 0.0;
    
    for (int i = 1; i < size; i++) {
        int dx = x[i] - x[i - 1];
        int dy = y[i] - y[i - 1];
        
        total_distance += sqrt(dx * dx + dy * dy);
        total_direction += atan2(dy, dx);
    }
    
    *avg_direction = total_direction / (size - 1);
    *avg_distance = total_distance / (size - 1);
}

static double calc_dist(int x1, int x2, int y1, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

static void print_int_arr(int *arr)
{
	for (int i = 0; arr[i]; i++)
		printf("%d\n", arr[i]);
}

int	main(void)
{
	printf("starting!\n");
	FILE *file = fopen("logfile.txt", "r");
	FILE *out = fopen("trans_logfile.txt", "w");
	int *x;
	int *y;
	int *true_y;
	int *true_x;
	int ll = count_lines(file);
	printf("there are %d items in the arrays, there are six arrays, there are %d items in all arrays total, and %d items in the input file\n", ll, ll * 6, ll * 4);
	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	rewind(file);
	char *stuff = malloc(sizeof(char) * file_size);
	fread(stuff, 1, file_size, file);
	char **arr = ft_split(stuff, '-');
	int arr_size = ll;
	x = malloc(sizeof(int) * (ll / 4));
	y = malloc(sizeof(int) * (ll / 4));
	true_x = malloc(sizeof(int) * (ll / 4));
	true_y = malloc(sizeof(int) * (ll / 4));
	int j = 0;
	for (int i = 0; i < ll; i++)
	{
		x[j] = atoi(arr[i]);
		i++;
		y[j] = atoi(arr[i]);
		i++;
		true_x[j] = atoi(arr[i]);
		i++;
		true_y[j] = atoi(arr[i]);
		j++;
	}
	double *u = malloc(sizeof(double) * ll / 4);
	for (int i = 0; i < ll / 4; i++)
		u[i] = calc_dist(x[i], x[i + 1], y[i], y[i + 1]);
	for (int i = 0; i < ll / 4; i++)
		fprintf(out, "distance to the next point\t\t=\t\t%0.3f\t\ty_distance\t=\t%d\t\tx_distance\t=\t%d\n", u[i], (x[i] > x[i + 1]) ? x[i] - x[i + 1] : x[i + 1] - x[i], (y[i] > y[i + 1]) ? y[i] - y[i + 1] : y[i + 1] - y[i]);
	double avg_direction, avg_distance;
	calculate_average_movement(x, y, ll / 4, &avg_direction, &avg_direction);
	fprintf(out, "the average distance traveld and direction traveled is respectively %0.3f\t\t%0.3f\n", avg_distance, avg_direction);
	fclose(file);
	fclose(out);
	free(x);
	free(y);
	free(true_y);
	free(true_x);
	free(stuff);
	for(int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
	free(u);
	printf("done!\n");
}