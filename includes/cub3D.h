/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:53:48 by mlow              #+#    #+#             */
/*   Updated: 2024/08/17 17:50:49 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../other_srcs/libft_project/libft.h"
# include "../other_srcs/printf_project/libftprintf.h"
# include "../other_srcs/get_next_line_project/get_next_line_bonus.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
//# include "MLX/MLX42.h" // include the mlx library


# define TEXTURE_SIZE 225
# define RICK_XPM "./assets/images/rick.xpm"
# define WALL_XPM "./assets/images/wall.xpm"
# define COIN_XPM "./assets/images/coin.xpm"
# define EXIT_XPM "./assets/images/exit.xpm"
# define EXITOPEN_XPM "./assets/images/exitopen.xpm"
# define PACMAN_XPM "./assets/images/pacman.xpm"

//define the keys
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC 65307

//define screen size
# define SCREEN_WIDTH 1280 // screen width 640
# define SCREEN_HEIGHT 960 // screen height 480
# define TILE_SIZE 100 // tile size

//define player
# define FOV_ANGLE 60 //how the player views the world
# define ROTATE_SPEED 0.045 // rotation speed
# define MOVE_SPEED 20 // player speed
# define RIGHT 0
# define LEFT 1
# define UP 2
# define DOWN 3

//define textures
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

//define dda_wall hit which
# define NORTH_SOUTH_SIDE 1
# define EAST_WEST_SIDE 0


//strutures

typedef struct s_element //the data structure
{
	//stores the data of
	//NO
	char	*north_texture;
	//SO
	char	*south_texture;
	//WE
	char	*west_texture;
	//EA
	char	*east_texture;
	//F
	int		floor_color[3];//R,G,B colors in range [0,255]: 0, 255, 255
	//C
	int		ceiling_color[3];//R,G,B colors in range [0,255]: 0, 255, 255
}				t_element;

typedef struct s_data //the data structure
{
	int		is_map_valid;//checking if map is even valid
	int		all_correct_elements;
	char	**map2d;// the map
	int		map_w;// map width/later player location
	int		map_h;// map height/later player location
	double		map_w_in_pixels;
	double		map_h_in_pixels;
	int		fd;
	double	distance;
	int 	flag;
	double	radfov;
}				t_data;

typedef struct s_player
{
	char		direction;//start direction
	int		pixel_x;//location of player in x in INT
	int		pixel_y;//location of player in y in INT
	double		p_x;// player x(width) position in the map
	double		p_y;// player y(height) position in the map
	double		dir_x;//where the direction player faces in x
	double		dir_y;//where the direction player faces in y
	double		plane_x;//the plane in x
	double		plane_y;//the plane in y
	double		sidedir_x;
	double		sidedir_y;
	int		step_x;
	int		step_y;
//	int		steps_taken;
	int		rotation; // rotation flag
	int		left_right; // left right flag
	int		up_down; // up down flag
	double	angle;  // player angle
	void	*start;
	void	**location;
}				t_player;

typedef struct s_raycasting //the ray structure
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_w;
	int		map_h;
	double	deltadist_x;
	double	deltadist_y;
	int		p_x;// player x(width) position in the map
	int		p_y;// player y(height) position in the map
	int		hit_side;
	double	perpwalldist;
	int	line_height;
	int	draw_start;
	int	draw_end;
	double	wall_x;
	
}				t_raycasting;

typedef struct	s_key
{
	int		map_x;
	int		map_y;
	int		w_pressed;
	int		a_pressed;
	int		s_pressed;
	int		d_pressed;
	int		left_rotate;
	int		right_rotate;
//	int		toggle_state;
//	int		keystate[65600];
}				t_key;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int				color;
}				t_mlx;


typedef struct s_img
{
	void			*img;
	int				*addr;
	int				pixel_bits;
	int				size_line;
	int				endian;
}					t_img;
//
/*
typedef struct		s_texture
{
}
*/

typedef struct s_game
{
	t_data		data;
	t_element	elements;
	t_player	player;
	t_raycasting	ray;
	t_key		key;
	t_mlx		mlx;
	t_img		img;
//images for textures
	int			**textures;
	int			**texture_pixels;
	int			texture_size;
//
	int			error_code;
	int			screen_x;
	int			screen_y;
}				t_game;

//main.c
int	start_the_game(char **argv);


//testmap.c
void	open_testmap(t_game *game, char *map_path);


//check.c
int	check_cub_valid_or_not(t_game *game, char **readmap);

//checkmap.c
int	checkmap_valid(t_game *game, char **map);

//fill_space.c
int	fill_space_tab(t_game *game, char ***tmp_map);
char	**fill_space_void(t_game *game, char **map);

//floodfill.c
void	map_floodfill(char ***tmp_map, t_game *game, int p_x, int p_y);
void	map_floodfill2(char ***tmp_map, t_game *game, int p_x, int p_y);
void	map_floodfill_checker(char ***tmp_map, t_game *game, int p_x, int p_y);

//freeing_struc.c
void	ftps_free(char **to_free);
void	free_double_pointers(char **split_map, char **get_texture);

//get_variables.c
char	*get_variable_cub(t_game *game);
void	get_variable_map(t_game *game, char **split_map);
int	get_variable_element(t_game *game, char **readmap);

//search_value_color.c
void	getting_color(char **map, char *var_name, int color[3]);
char	*search_for_value(char **split_map, char *var_name);

//init_variables.c
void	init_variables(t_game *game);
void	init_variable_player(t_game *game);

//invalid_window_size_checker.c
void	invalid_window_size_checker(t_game *game);

//----------------------------------------------------------
//----------------------------------------------------------
//--------new additions----------
//window_screen_creation.c
void	window_screen_creation(t_game *game);
//texture.c
void	setup_texture(t_game *game);
void	init_texture_pixels(t_game *game);
void	init_texture_img(t_game *game, t_img *tmp, char *path);
//mousekey_hook.c
int		keyhook(int keycode, t_game *game);
int		keyhook_release(int keycode, t_game *game);
void	khook(t_game *game, double move_x, double move_y);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, int i);
//game
int gameplay(t_game *game);
//--------new additions----------
//----------------------------------------------------------
//----------------------------------------------------------

//ft_strcmp.c
int	ft_strcmp(char *s1, char *s2);

//print_msg
void	print_msg(char *message, int exit_code);

//exit_function.c
void	free_gameloop_end(char *message, int exit_code, t_game *game);
void	free_end_exit(char *message, int exit_code, t_game *game, char **str);

//exit_utils.c
int	x_close_window(t_game *game);
int	game_checkerror_exit(char *message, t_game *game);

//mlxpixel.c
void	mlxpixel(t_game *game, int x, int y, int color);
void	mlxpixel_on_screen(t_game *game);

//mlximage.c
void	mlximage_on_screen(t_game *game);

//draw_display.c
void	draw_display(t_game *game);



#endif
/*
#include <unistd.h> // for fork() / execve() / access()
#include <stdio.h> // for printf()
#include <stdlib.h> // exit()
#include <fcntl.h> //open()
#include <sys/wait.h> // wait() / waitpid()
#include <sys/types.h> //for wait() / fork() / pid_t() / wait() / waitpid()
#include <errno.h> // for perror()
*/
