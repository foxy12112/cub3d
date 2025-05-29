/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:51:03 by ldick             #+#    #+#             */
/*   Updated: 2025/05/29 16:34:39 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*rm_s(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
		i++;
	if (i == len)
	{
		str[0] = '\0';
		return (str);
	}
	while (i < len)
		str[j++] = str[i++];
	str[j] = '\0';
	len = ft_strlen(str) - 1;
	while (len >= 0 && (str[len] == ' ' || str[len] == '\t'
			|| str[len] == '\n' || str[len] == '\r'))
		str[len--] = '\0';
	return (str);
}

unsigned int	get_color(int r, int g, int b, int a)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0
		&& b <= 255 && a >= 0 && a <= 255)
		return ((r << 24) | (g << 16) | (b << 8) | a);
	return (0);
}
