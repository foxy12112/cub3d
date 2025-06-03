/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:50:02 by foxy              #+#    #+#             */
/*   Updated: 2025/06/03 11:13:17 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libs.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SPEED 0.1
# define LENGTH 5
# define ROT_SPEED 0.05
# define RECTANGLE 20
# define PLAYER_SIZE 10
# define FOV 90
# define NORTH 0
# define WEST 270
# define SOUTH 180
# define EAST 90
# define HEIGHT 1080
# define WIDHT 1920
# define TEX_WIDTH 1024
# define TEX_HEIGHT 1024
# define MAX_MAP_LINES 1000

typedef struct s_minimap_data
{
	int				top_left;
	int				top_right;
	int				bottom_left;
	int				bottom_right;
	int				tile_size;
	int				scale;
	int				width;
	int				height;
}					t_minimap_data;

typedef struct s_raycasting
{
	int				map_x;
	int				map_y;
	double			sidedist_y;
	double			sidedist_x;
	double			deltadist_x;
	double			deltadist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				side;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
}					t_raycasting;

typedef struct s_drawing
{
	int				tex_x;
	int				tex_y;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_drawing;

typedef struct s_direction
{
	double			temp_dir_x;
	double			temp_dir_y;
	double			dir_inc;
}					t_direction;

typedef struct s_validation_counter
{
	int			west_texture;
	int			east_texture;
	int			north_texture;
	int			south_texture;
	int			ceiling;
	int			floor;
}				t_validation_counter;
typedef struct s_cub_data
{
	mlx_t					*mlx;
	mlx_image_t				*img;
	mlx_image_t				*omg;
	char					*map_path;
	mlx_texture_t			*texture_north;
	mlx_texture_t			*texture_south;
	mlx_texture_t			*texture_east;
	mlx_texture_t			*texture_west;
	int						floor;
	int						ceiling;
	char					**map;
	int						map_height;
	int						map_width;
	double					player_y;
	double					player_x;
	double					player_direction_x;
	double					player_direction_y;
	double					player_plane_x;
	double					player_plane_y;
	double					player_start_x;
	double					player_start_y;
	t_minimap_data			minimap;
	t_drawing				draw;
	bool					mouse_on_off;
	t_validation_counter	counter;
}					t_cub_data;

// INIT
int					init(char **argv, t_cub_data *cub);

// INIT_UTILS
int					check_extension(char *path);

void				init_dda(t_cub_data *cub, t_raycasting *ray, int x);
void				choose_step(t_cub_data *cub, t_raycasting *ray);
// PARSING
int					parsing(t_cub_data *cub);
// PARSING_UTILS
int					get_background(char *line);
int					add_textures(t_cub_data *cub);
int					add_player(t_cub_data *cub);
int					add_map(t_cub_data *cub);
// VALIDATE
int					validate(t_cub_data *cub);

// UTILS
unsigned int		get_color(int r, int g, int b, int a);
char				*rm_s(char *str);
void				free_split(char **split);

// EVENTS
void				events(void *param);
// int					is_valid_location(t_cub_data *cub, int x, int y);
int					is_valid_location(t_cub_data *cub, double x, double y);
// DRAWING
void				draw_background(t_cub_data *cub);
mlx_texture_t		*select_texture(t_cub_data *cub, t_raycasting ray);
int					calculate_texture(t_cub_data *cub, t_raycasting ray,
						mlx_texture_t *tex);
unsigned int		get_pixel_color(uint8_t *p);
void				draw_line(t_raycasting ray, t_cub_data *cub, int x);
// GAME
int					game(t_cub_data *cub);
void				dda_loop(t_cub_data *cub);
void				rotate(t_cub_data *cub, int direction);
void				mouse(t_cub_data *cub);
void				movement(t_cub_data *cub);
void				copy_pixels(uint8_t *dst, uint8_t *src);
void				scale(mlx_texture_t *new, mlx_texture_t *old);
mlx_texture_t		*correct_texture(char *line);
int					validate_textures(t_cub_data *cub);
void				correct_map(t_cub_data *cub);
void				movement_vertical(t_cub_data *cub);
void				draw_player(t_cub_data *cub);
t_raycasting		perform_dda(t_raycasting ray, t_cub_data *cub);
void				free_texture(t_cub_data *cub);

#endif
