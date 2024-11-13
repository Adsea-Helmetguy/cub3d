/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:53:48 by mlow              #+#    #+#             */
/*   Updated: 2024/11/12 15:21:06 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../other_srcs/get_next_line_project/get_next_line_bonus.h"
# include "../other_srcs/libft_project/libft.h"
# include "../other_srcs/printf_project/libftprintf.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
//# include "MLX/MLX42.h" // include the mlx library

// define the keys
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC 65307

// define screen size
# define SCREEN_WIDTH 640  // screen width 640
# define SCREEN_HEIGHT 480 // screen height 480
# define TEXTURE_SIZE 800  // Texture_size
# define TILE_SIZE 225     // tile size

// define player
# define FOV_ANGLE 60       // how the player views the world
# define ROTATE_SPEED 0.045 // rotation speed
# define MOVE_SPEED 80      // player speed
# define RIGHT 0
# define LEFT 1
# define UP 2
# define DOWN 3

// define textures
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

// define dda_wall hit which
# define NORTH_SOUTH_SIDE 1
# define EAST_WEST_SIDE 0

// strutures
typedef struct s_getcolor
{
	char			*element_color;
	char			**game_color;
	int				array;
	int				index;
	int				all_digits;
	int				before_mod;
	char			*rgb_colors;

}					t_getcolor;

typedef struct s_element
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
}				t_element;

typedef struct s_data
{
	int		is_map_valid;
	int		all_correct_elements;
	char	**map2d;
	int		map_w;
	int		map_h;
	double	map_w_in_pixels;
	double	map_h_in_pixels;
	int		fd;
	double	distance;
	int		flag;
	double	radfov;
}				t_data;

typedef struct s_player
{
	char	direction;
	int		pixel_x;
	int		pixel_y;
	double	p_x;
	double	p_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	sidedir_x;
	double	sidedir_y;
	int		step_x;
	int		step_y;
	int		rotation;
	int		left_right;
	int		up_down;
	double	angle;
	void	*start;
	void	**location;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
}				t_player;

typedef struct s_raycasting
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_w;
	int		map_h;
	double	deltadist_x;
	double	deltadist_y;
	int		p_x;
	int		p_y;
	int		hit_side;
	double	perpwalldist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;

}				t_raycasting;

typedef struct s_key
{
	int		map_x;
	int		map_y;
	int		w_pressed;
	int		a_pressed;
	int		s_pressed;
	int		d_pressed;
	int		left_rotate;
	int		right_rotate;
}				t_key;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
}				t_mlx;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_game
{
	t_data			data;
	t_element		elements;
	t_player		player;
	t_raycasting	ray;
	t_key			key;
	t_mlx			mlx;
	t_img			img;
	int				**textures;
	int				texture_width[4];
	int				texture_height[4];
	int				error_code;
	int				screen_x;
	int				screen_y;
}					t_game;

// main.c
int			start_the_game(char **argv);

// testmap.c
void		open_testmap(t_game *game, char *map_path);

// check.c
int			check_cub_valid_or_not(t_game *game, char **readmap);

// checkmap.c
int			checkmap_valid(t_game *game, char **data_map2d);
char		*ft_strdup_checkmap(const char *s);
char		**tmp_map2_helper(t_game *game, char **tmp_map);

// fill_space.c
int			fill_space_tab(t_game *game, char ***tmp_map);
char		**fill_space_void(t_game *game, char **map);

// floodfill.c
void		map_floodfill(char ***tmp_map, t_game *game, int p_x, int p_y);
void		map_floodfill2(char ***tmp_map, t_game *game, int p_x, int p_y);
void		map_floodfill_checker(char ***tmp_map, t_game *game, \
				int p_x, int p_y);

// freeing_struc.c
void		free_textures(int **game_textures);
void		ftps_free(char **to_free);

// get_variables.c
char		*get_variable_cub(t_game *game);
void		get_variable_map(t_game *game, char **split_map);
int			get_variable_element(t_game *game, char **readmap);

// search_value_color.c
int			getting_color(char **map, char *var_name, int color[3]);
char		*search_for_value(char **split_map, char *var_name);

// init_variables.c
void		init_variables(t_game *game);
void		init_variables2(t_game *game);
void		init_variable_player(t_game *game);

// window_screen_creation.c
void		window_screen_creation(t_game *game);
// texture.c
void		setup_texture(t_game *game);
void		init_texture_img(t_game *game, t_img *tmp, char *path, int face);
// mousekey_hook.c
int			keyhook(int keycode, t_game *game);
int			keyhook_release(int keycode, t_game *game);
void		khook(t_game *game, double move_x, double move_y);
void		move_player(t_game *game, double move_x, double move_y);
void		rotate_player(t_game *game, int i);
// game
int			gameplay(t_game *game);

// ft_strcmp.c
int			ft_strcmp(char *s1, char *s2);

// print_msg
void		print_msg(char *message, int exit_code);

// exit_function.c
void		free_gameloop_end(char *message, int exit_code, t_game *game);
void		free_end_exit(char *message, int exit_code, \
				t_game *game, char **str);
void		free_before_game(char *message, int exit_code, t_game *game);

// exit_utils.c
int			x_close_window(t_game *game);
int			close_window_invalidtextures(t_game *game);
int			game_checkerror_exit(char *message, t_game *game);
int			array_free_exit(char *message, t_game *game, char ***to_free);

// mlxpixel.c
void		mlxpixel(t_game *game, int x, int y, int color);
void		mlxpixel_on_screen(t_game *game);

// raycasting.c
void		raycasting(t_game *game);
int			x_positive(double angle);
int			y_positive(double angle);
double		nor_angle(double angle);
void		render(t_game *game, int ray, double angle);

// ray_utils.c
int			init_h(double angle, double *x_step, double *y_step, \
				double *y_intercept);
int			init_v(double angle, double *x_step, double *y_step, \
				double *x_intercept);

#endif
