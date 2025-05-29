/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foxy <foxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:50:02 by foxy              #+#    #+#             */
/*   Updated: 2025/05/29 18:32:23 by foxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <ctype.h>
# include <limits.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define SPEED 0.1
# define LENGTH 5
# define ROT_SPEED 0.05
# define RECTANGLE 20
# define PSIZE 10
# define FOV 90
# define NORTH 0
# define WEST 270
# define SOUTH 180
# define EAST 90
# define HEIGHT 1080
# define WIDHT 1920
# define TEX_WIDTH 1024
# define TEX_HEIGHT 1024

typedef struct s_minimap_data
{
	int			top_left;
	int			top_right;
	int			bottom_left;
	int			bottom_right;
	int			tile_size;
	int			scale;
	int			width;
	int			height;
}				t_minimap_data;

typedef struct s_raycasting
{
	int			map_x;
	int			map_y;
	double		sidedist_y;
	double		sidedist_x;
	double		deltadist_x;
	double		deltadist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
}				t_raycasting;

typedef struct s_drawing
{
	int				tex_x;
	int				tex_y;
	double			wall_x;
	double			step;
	double			tex_pos;
}				t_drawing;

typedef struct s_direction
{
	double	temp_dir_x;
	double	temp_dir_y;
	double	dir_inc;
}				t_direction;

typedef struct s_cub_data
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*omg;
	char				*map_path;
	mlx_texture_t		*texture_north;
	mlx_texture_t		*texture_south;
	mlx_texture_t		*texture_east;
	mlx_texture_t		*texture_west;
	int					floor;
	int					ceiling;
	char				**map;
	int					map_height;
	int					map_width;
	double				player_y;
	double				player_x;
	double				player_direction_x;
	double				player_direction_y;
	double				player_plane_x;
	double				player_plane_y;
	t_minimap_data		minimap;
	t_drawing			draw;
}				t_cub_data;

//INIT
int				init(char **argv, t_cub_data *cub);

//INIT_UTILS
int	check_extension(char *path);

void	init_dda(t_cub_data *cub, t_raycasting *ray, int x, t_direction dir);
void	choose_step(t_cub_data *cub, t_raycasting *ray);
//PARSING
int				parsing(t_cub_data *cub);
//PARSING_UTILS
int				get_background(char *line, int *i);
int				add_textures(t_cub_data *cub);
int				add_player(t_cub_data *cub);
int				add_map(t_cub_data *cub);
//VALIDATE
int				validate(t_cub_data *cub);

//UTILS
unsigned int	get_color(int r, int g, int b, int a);
char			*rm_s(char *str);
void	free_split(char **split);

//EVENTS
void	events(void *param);
int	is_valid_location(t_cub_data *cub, int move_speed, int x, int y);

//DRAWING
void	draw_background(t_cub_data *cub);
void	bresenham(int x0, int y0, int x1, int y1, t_cub_data *cub);
mlx_texture_t *select_texture(t_cub_data *cub, t_raycasting ray);
int	calculate_texture(t_cub_data *cub, t_raycasting ray, mlx_texture_t *tex);
//GAME
int game(t_cub_data *cub);
void	dda_loop(t_cub_data *cub);

#endif
