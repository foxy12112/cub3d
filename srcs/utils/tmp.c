/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:47:25 by ldick             #+#    #+#             */
/*   Updated: 2025/02/25 11:13:03 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*safe_malloc(size_t size, t_cub_data *cub, const char *func_name)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("malloc error in funciton %s\n", func_name);
		clean_all(cub);
		exit (EXIT_FAILURE);
	}
	return (ptr);
}

int		percent(double value, double total)
{
	return ((value / total) * 100);
}

void	ft_swap(void *a, void *b, size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (tmp)
	{
		ft_memcpy(tmp, a, size);
		ft_memcpy(a, b, size);
		ft_memcpy(b, tmp, size);
		free(tmp);
	}
}