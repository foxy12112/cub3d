/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:03:26 by petrasostar       #+#    #+#             */
/*   Updated: 2025/03/10 08:09:38 by petrasostar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	PARSE_RGB_LINE

	Checks whether the RGB line has exactly two commas and whether it contains only numbers and commas.
*/

int	parse_rgb_line(char *line)
{
	int	i = 0;
	int	comma = 0;

	if (!isdigit(line[0]) || !isdigit(line[ft_strlen(line) - 1]))
		return (0);

	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		else if (!isdigit(line[i]) && line[i] != ' ')  
			return (0);  // If it is not a digit and not a comma → error

		if (line[i] == ',' && line[i + 1] == ',')
			return (0);  // There must not be two consecutive commas
		i++;
	}

	return (comma == 2);  // Exactly two commas means correct format
}

/*
	CHECK_RGB

	Parses the numbers and the full `rgb` string, checking if they are in the range [0,255].
*/

int	check_rgb(int *rgb, char *line)
{
	int	i = 0;
	int	j = 0;

	if (!parse_rgb_line(line))
		return (0);

	rgb[j++] = ft_atoi(line);

	while (line[i] && j < 3)
	{
		if (line[i] == ',')
			rgb[j++] = ft_atoi(line + i + 1);
		i++;
	}

	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
		return (0);

	return (1);
}

/*
	GET_RGB

	It checks the format and calls `check_rgb()`. If it is wrong, it reports an error.
*/

void get_rgb(t_cub_data *map, int *rgb, char **split_line)

{
	int	count = 0;

	while (split_line[count])
		count++;

	if (count != 2 || !check_rgb(rgb, split_line[1]))
	{
		free_double_array(split_line);
		ft_error(map, "Error\nRGB line is incorrect\n");
	}

	free_double_array(split_line);
}
