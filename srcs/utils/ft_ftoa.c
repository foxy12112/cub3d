/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:52:47 by ldick             #+#    #+#             */
/*   Updated: 2025/04/15 12:04:43 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reverse(char *str, int len)
{
	int	i;
	int	j;
	int	temp;

	temp = 0;
	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int	int_to_str(int x, char str[], int d)
{
	int	i;

	i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	while (i < d)
		str[i++] = '0';
	reverse(str, i);
	str[i] = '\0';
	return (i);
}

void	ft_ftoa(double n, char *res, int afterpoint)
{
	int		ipart;
	double	fpart;
	int		i;

	ipart = (int)n;
	fpart = n - (double)ipart;
	i = int_to_str(ipart, res, 0);
	if (afterpoint != 0)
	{
		res[i] = '.';
		fpart = fpart * pow(10, afterpoint);
		int_to_str((int)fpart, res + i + 1, afterpoint);
	}
}
