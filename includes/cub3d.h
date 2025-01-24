/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:50:02 by foxy              #+#    #+#             */
/*   Updated: 2025/01/24 18:06:48 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include "libs.h"


typedef struct s_floor_data
{
	char				*floor;
	int					r;
	int					g;
	int					b;
}						t_floor_data;

typedef struct s_ceiling_data
{
	char				*ceiling;
	int					r;
	int					g;
	int					b;
}						t_ceiling_data;

typedef struct s_texture_data
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	t_floor_data		*floor;
	t_ceiling_data		*ceiling;
}						t_texture_data;

typedef struct s_cub_data
{
	char				**map;
	t_texture_data		*texture;
}						t_cub_data;


void		clean_all(t_cub_data *cub);
void		*safe_malloc(size_t size, t_cub_data *cub, const char *func_name);
void		ft_error(void);
int			init(char *argv[], t_cub_data *cub);
int			add_texture(int i, t_texture_data *texture, char *line);
char		*rm_s(char *str);
int			init_map(t_cub_data *cub, int fd, char *line);
int			init_color(t_texture_data *texture);

#endif