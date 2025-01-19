/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:47:25 by ldick             #+#    #+#             */
/*   Updated: 2025/01/19 18:00:56 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*safe_malloc(size_t size, t_cub_data *cub)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("malloc error\n");
		clean_all(cub);
		exit (EXIT_FAILURE);
	}
	return (ptr);
}