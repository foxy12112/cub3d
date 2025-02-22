/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foxy <foxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:50:02 by foxy              #+#    #+#             */
/*   Updated: 2025/02/22 17:32:04 by foxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include "libs.h"

# define RECTANGLE 20
# define PSIZE 10
# define FOV 90

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
	mlx_image_t			*no_tex;
	mlx_image_t			*so_tex;
	mlx_image_t			*we_tex;
	mlx_image_t			*ea_tex;
	t_floor_data		*floor;
	t_ceiling_data		*ceiling;
}						t_texture_data;

typedef struct s_player_data
{
	int					start_x;
	int					start_y;
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
}						t_player_data;

typedef struct s_mlx
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	int					width;
	int					height;
}						t_mlx;

typedef struct s_minimap
{
	mlx_image_t			*img;
	mlx_image_t			*p_img;
	double				scale_x;
	double				scale_y;
	double				scale;
	int					size_x;
	int					size_y;
}						t_minimap;

typedef struct s_textbox
{
	mlx_image_t			*img;
	int					active;
	char				*text;
}						t_textbox;

typedef struct s_cub_data
{
	char				**map;
	int					x;
	int					y;
	int					floor;
	int					ceiling;
	t_texture_data		*texture;
	t_player_data		*p;
	mlx_t				*mlx;
	mlx_image_t			*img;
	t_minimap			*minimap;
	t_textbox			*text;
}						t_cub_data;


void			clean_all(t_cub_data *cub);
void			*safe_malloc(size_t size, t_cub_data *cub, const char *func_name);
void			ft_error(t_cub_data *cub, char *error_msg);
int				init(char *argv[], t_cub_data *cub);
int				add_texture(int i, t_texture_data *texture, char *line);
char			*rm_s(char *str);
int				init_map(t_cub_data *cub, int fd);
int				init_color(t_texture_data *texture);
void			*create_image(t_cub_data *cub, char *str);
int				check_textures(t_cub_data *cub);
int				parsing(t_cub_data *cub);
int				check_map(t_cub_data *cub);
int				check_bottom(t_cub_data *cub);
int				check_top(t_cub_data *cub);
int				check_sides(t_cub_data *cub);
void			game_loop(t_cub_data *cub);
int				get_color(int r, int g, int b, int a);
int				check_leaks(char **map, t_cub_data *cub);
void			printMap(char **map);
void			event_handler(mlx_key_data_t mkd, void *param);
void			map(t_cub_data *cub);
void			event(mlx_key_data_t mkd, void *param);
void			ft_ftoa(double n, char *res, int afterpoint);
void			draw_player(t_cub_data *cub);
int				percent(double value, double total);
void			scaling(t_cub_data *cub);
// int			collision(t_cub_data *cub);
bool			collision_left(t_cub_data *cub);
bool			collision_right(t_cub_data *cub);
bool			collision_top(t_cub_data *cub);
bool			collision_bottom(t_cub_data *cub);
void			scale(mlx_texture_t *new, mlx_texture_t *tex, int width, int height);
mlx_texture_t	*scale_tex(mlx_texture_t *texture, int width, int height);


#endif