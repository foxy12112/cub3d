/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:50:02 by foxy              #+#    #+#             */
/*   Updated: 2025/05/11 15:10:38 by ldick            ###   ########.fr       */
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

# define SPEED 1
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
# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FAILURE
#  define FAILURE -1
# endif

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
	mlx_texture_t		*no_tex;
	mlx_texture_t		*so_tex;
	mlx_texture_t		*we_tex;
	mlx_texture_t		*ea_tex;
	mlx_texture_t		*missing_texture;
	t_floor_data		*floor;
	t_ceiling_data		*ceiling;
}						t_texture_data;

typedef struct s_player_data
{
	int					start_x;
	int					start_y;
	double				x;
	double				y;
	double				dir;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				camera_angle;
	int					perp_wall_dist;
}						t_player_data;

typedef struct s_loc
{
	int					x;
	int					y;
}						t_loc;

typedef struct s_move_data
{
	int					x[30];
	int					y[30];
}						t_move_data;

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
	bool				flag;
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
	int					map_height;
	int					map_width;
	t_texture_data		*texture;
	t_player_data		*p;
	mlx_t				*mlx;
	mlx_image_t			*img;
	t_minimap			*minimap;
	t_textbox			*text;
	t_move_data			*move;
	int					calculated;
	double				ray_dir_x;
	double				ray_dir_y;
	double				time;
	int					side;
	double              delta_dist_x;
    double              delta_dist_y;
    double              side_dist_x;
    double              side_dist_y;
    int                 step_x;
    int                 step_y;
    int                 map_x;
    int                 map_y;
    double              perpwalldist;
	int					hit_x;
	int					hit_y;
	int					wall_amount;
}						t_cub_data;

void			clean_all(t_cub_data *cub);
void			*safe_malloc(size_t size, t_cub_data *cub, const char *func_name);
void			ft_error(t_cub_data *cub, const char *error_msg);
int				init(char *argv[], t_cub_data *cub);
int				add_texture(int i, t_texture_data *texture, char *line);
char			*rm_s(char *str);
int				init_map(t_cub_data *cub, int fd);
int				init_color(t_texture_data *texture);
mlx_texture_t	*create_image(t_cub_data *cub, char *str);
void			game_loop(t_cub_data *cub);
unsigned int				get_color(int r, int g, int b, int a);
void			event_handler(mlx_key_data_t mkd, void *param);
void			map(t_cub_data *cub);
void			event(mlx_key_data_t mkd, void *param);
void			ft_ftoa(double n, char *res, int afterpoint);
void			draw_player(t_cub_data *cub);
int				percent(double value, double total);
void			draw_ray(t_cub_data *cub);
// int			collision(t_cub_data *cub);
bool			collision_left(t_cub_data *cub);
bool			collision_right(t_cub_data *cub);
bool			collision_top(t_cub_data *cub);
bool			collision_bottom(t_cub_data *cub);
void			scale(mlx_texture_t *new, mlx_texture_t *tex, int width, int height);
mlx_texture_t	*scale_tex(mlx_texture_t *texture, int width, int height);
bool			touch(double px, double py, t_cub_data *cub);

void			draw_c_f(t_cub_data *cub);
void			draw_line(int x0, int y0, int x1, int y1, t_cub_data *cub);
void			ft_swap(void *a, void *b, size_t size);
int				ft_abs(int value);
void			draw_fov(t_cub_data *cub);

void			calc_location(t_cub_data *cub, double angle);
int				check_texture_file(char *path, char *texture_name);
int				check_texture_format(const char *path);

//parsing
int				parsing(t_cub_data *cub);
int				check_map(t_cub_data *cub);
int				check_map_exists(t_cub_data *cub);
int				check_top(t_cub_data *cub);
int				check_bottom(t_cub_data *cub);
int				check_sides(t_cub_data *cub);
// int				check_player(t_cub_data *cub);
int				check_leaks(char **map, t_cub_data *cub);
int				check_map_validity(t_cub_data *cub);
int				check_map_dim(t_cub_data *cub);
int				check_row(t_cub_data *cub);
int				check_map_elements(t_cub_data *cub);
int				check_invalid_chars(t_cub_data *cub);
int				check_texture(const char *path, const char *texture_name);
int				check_textures(t_cub_data *cub);
int				parse_rgb_line(char *line);
int				check_rgb(int *rgb, char *line);
void			get_rgb(t_cub_data *map, int *rgb, char **split_line);
void			printMap(t_cub_data *cub);
void			free_double_array(char **array);

//debug
void			print_map_lines(char **map);
void			print_minimap_data(t_minimap *minimap);
void			print_mapinfo(t_cub_data *data);
void			print_player_info(t_cub_data *data);
void			display_data(t_cub_data *data);
int				raytrace(t_cub_data *cub);
bool			collision(t_cub_data *cub);
double	correct_dir(double angle);

// // ========== RAYCASTING ==========
void	raycasting(t_cub_data *cub);
void	init_ray(t_cub_data *cub, int x);
void	calculate_dist(t_cub_data *cub);
void	calculate_step(t_cub_data *cub);
void	perform_dda(t_cub_data *cub);
void	calculate_column(t_cub_data *cub, int *line_height, int *start, int *end);
// void	calculate_texture(t_cub_data *cub);
int		calculate_texture(t_cub_data *cub, mlx_image_t *tex);

void	draw_texture(t_cub_data *cub, int x, int texture);
void	draw_column(t_cub_data *cub, int x);
void	img_pix_put(t_cub_data *cub, int x, int y, int color);

//parsing
int				parsing(t_cub_data *cub);
int				check_map(t_cub_data *cub);
int				check_map_exists(t_cub_data *cub);
int				check_top(t_cub_data *cub);
int				check_bottom(t_cub_data *cub);
int				check_sides(t_cub_data *cub);
int				check_player(t_cub_data *cub);
int				check_leaks(char **map, t_cub_data *cub);
int				check_map_validity(t_cub_data *cub);
int				check_map_dim(t_cub_data *cub);
int				check_row(t_cub_data *cub);
int				check_map_elements(t_cub_data *cub);
int				check_invalid_chars(t_cub_data *cub);
int				check_textures(t_cub_data *cub);
int				parse_rgb_line(char *line);
int				check_rgb(int *rgb, char *line);
void			get_rgb(t_cub_data *map, int *rgb, char **split_line);
void			print_map(t_cub_data *cub);
void			free_double_array(char **array);
void			set_player_position(t_cub_data *cub, int j, int i, char c);
int				check_and_find_player(t_cub_data *cub);
void			set_player_direction(t_cub_data *cub, char c);

//init
int				init_texture(t_cub_data *cub);
int				add_texture(int i, t_texture_data *texture, char *line);
int				init_map(t_cub_data *cub, int fd);
int				init_color(t_texture_data *texture);
void			reverse(char *str, int len);
int				int_to_str(int x, char str[], int d);
void			ft_ftoa(double n, char *res, int afterpoint);
char			*rm_s(char *str);
mlx_texture_t	*scale_tex(mlx_texture_t *texture, int width, int height);
// void			*create_image(t_cub_data *cub, char *str);
// int				get_color(int r, int g, int b, int a);
void			init_player(t_cub_data *cub);
int				init(char *argv[], t_cub_data *cub);
void			*safe_malloc(size_t size, t_cub_data *cub, const char *func_name);
int				percent(double value, double total);
void			ft_swap(void *a, void *b, size_t size);
int				ft_abs(int value);
unsigned int	get_pixel_color(uint8_t *p);

int	valid_location(int x, int y, t_cub_data *cub);
mlx_texture_t	*get_wall_texture(t_cub_data *cub);
bool	is_wall(t_cub_data *cub, int hit_x, int hit_y);
int	is_out_of_bound(char **map, int x, int y);


#endif
//TODO change tenary operators to normal if condition