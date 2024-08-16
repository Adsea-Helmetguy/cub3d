whatsup~~~~

Today i will be going through how i would do the project.
In so_long i will be going through the makefile first as to do the project we
need the makefile to compile and make it work.


====================================================

Notes for the flags:
# -l : tells it which library to use
# -L : tells it which path to look for the library
# -I : where to look for .h file
====================================================



Firstly, we need to go through these parts.
We need to name our makefile once we compile it, i choose to call it
so_long.
While we have the basics CC = gcc & the CFLAGS = -Wall -Werror -Wextra -g.
Also we need the -g for the valgrind & gdb.
Then SRC_DIR and INC_DIR are pretty basic, SRC_DIR is the location where
our main files are located while INC_DIR is the location of our so_long.h file.
--------------------------------------------------------------------------------------------
NAME = so_long

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
SRC_DIR = ./main_src
INC_DIR = ./includes

--------------------------------------------------------------------------------------------






Below the LIBFT_SRC_DIR is the file location for our LIBFT. LIBFT = $(LIBFT_SRC_DIR)/libft.a
is our archive file. And then we are at LIB_FLAGS.
-L $(LIBFT_SRC_DIR) <- specifies the directory where the linker (-L) should look for.
-lft is a bit unique. This flag specifies the name of the library to link against. Bascially,
it is libft but without the "lib" part. we use -l to link and then 3 letters after which is
"ft". This will connect to my folder ./other_srcs/libft_project and look for libft.a.
(question u might ask: "well what about libft.h?"
-answer: Well no, it deals with the linker and library files, not header files like libft.h.)
--------------------------------------------------------------------------------------------
#LIBFT file names and paths
LIBFT_SRC_DIR = ./other_srcs/libft_project
LIBFT = $(LIBFT_SRC_DIR)/libft.a
LIB_FLAGS = -L $(LIBFT_SRC_DIR) -lft

--------------------------------------------------------------------------------------------








Below is the Printf section with the same idea as above:
--------------------------------------------------------------------------------------------
#PRINTF file names and paths
PRINTF_SRC_DIR = ./other_srcs/printf_project
PRINTF = $(PRINTF_SRC_DIR)/libftprintf.a
PRINTF_FLAGS = -L $(PRINTF_SRC_DIR) -lftprintf

--------------------------------------------------------------------------------------------









Same for Get_Next_Line. While i do know that you dont use make file to hand in this 
particular project, i made a makefile for this particular project so that it can work 
alongside with my other Makefiles.
--------------------------------------------------------------------------------------------
#GET_NEXT_LINE file names and paths
GNL_SRC_DIR = ./other_srcs/get_next_line_project
GNL = $(GNL_SRC_DIR)/libft_get_next_line.a
GNL_FLAGS = -L $(GNL_SRC_DIR) -lft_get_next_line


Just in case, here is a sample Makefile for my Get_next_line. (I use bonus only).
==========================================================================
NAME = libft_get_next_line.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR =.
INC_DIR =.

# BONUS source files
BONUS_FILE_NAMES =  get_next_line_bonus.c \
		get_next_line_utils_bonus.c 

#BONUS source files names to full paths
BONUS_FILE_PATHS = $(addprefix $(SRC_DIR)/, $(BONUS_FILE_NAMES))

#Generate corresponding project file names
BONUS_OBJ_FILE_PATHS = $(BONUS_FILE_PATHS:.c=.o)

all: $(NAME)


$(NAME): $(BONUS_OBJ_FILE_PATHS)
	ar rcs $(NAME) $(BONUS_OBJ_FILE_PATHS)


$(BONUS_OBJ_FILE_PATHS): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@ 
	
#create rule to compile individual source files for bonus to object files
clean:
	rm -f $(OBJ_FILE_PATHS) $(BONUS_OBJ_FILE_PATHS)

fclean: clean
	rm -f $(NAME)

bonus: $(BONUS_OBJ_FILE_PATHS)
	ar rcs $(NAME) $(BONUS_OBJ_FILE_PATHS)

re: fclean all

.PHONY: all clean fclean re bonus
==========================================================================
--------------------------------------------------------------------------------------------





Now that we are here we need to ALSO create a director and archive for the minilibx.
We can do so with the following:
-For the MLX_INC_HEADER_DIR. We need "-I/usr/include" because the header "X.h" is located at
that location. We need several other *.h files there as well so -I @ the usr/include is 
good enough. Those we (might need) are:
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h> 
# include <X11/X.h>
# include <X11/keysym.h>
Remember to include these in your SO_LONG.H file okay? Cause even if you dont use them,
its not a penatly.
Except for fcntl.h, u need them to use open() unless your other *.h files have them.
But just add them in anyways.....
--------------------------------------------------------------------------------------------
#MLX file names and paths
#could be /usr/lib, depends on where you decided to put your mlx'
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a 

MLX_INC_HEADER_DIR = -I/usr/include -I $(MLX_DIR)
MLX_FLAGS  = -L $(MLX_LIB) -lmlx -L/usr/lib/X11 -lXext -lX11

# -l : tells it which library to use
# -L : tells it which path to look for the library
# -I : where to look for .h file

#MLX_FLAGS  = -L$(MLX_DIR) -lmlx -L${LIBFT} -lft # if you decided to install libmlx.a locally you don't need "-L$(LIBMLX) -lmlx" the school also has it locally as well...
#Location for archive files, you will need more than these 2.
--------------------------------------------------------------------------------------------










Following below are the folders i used:
--------------------------------------------------------------------------------------------
# ************************************************************************** */
#	SOURCE                                                               */
# ************************************************************************** */
#List of SOURCE(SRC) files
SRC_FILE_NAMES = window_so_long.c \
		mousekey_hook.c \
		exit_utils.c \
		message.c \
		testmap.c \
		empty.c \
		wall.c \
		coin.c \
		door.c \
		player.c \
		player_movements.c \
		vaild_path.c \
		invalid.c 
		
# ************************************************************************** */
#	FILE_LOCATION                                                        */
# ************************************************************************** */
SRC_FILE_PATHS = $(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
GNL_FILE_PATHS = $(addprefix $(GNL_SRC_DIR)/, $(GNL_FILE_NAMES))

OBJ_FILE_PATHS = $(SRC_FILE_PATHS:.c=.o)
GNL_OBJ_FILE_PATHS = $(SRC_FILE_PATHS:.c=.o)
--------------------------------------------------------------------------------------------








Now we go to the Rules part:
-Pretty standard we include "all" and the "name". This depends on how you write but for
reference, u can look at below.
If u are unsure about the flags, please refer to the lines 8-14 and those at the beginning.
--------------------------------------------------------------------------------------------
# ************************************************************************** */
#	RULES                                                                */
# ************************************************************************** */
all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJ_FILE_PATHS) $(LIBFT) $(PRINTF) $(GNL)
	$(CC) $(OBJ_FILE_PATHS) $(MLX_LIB) -Lminilibx-linux -L$(MLX_FLAGS) $(LIB_FLAGS) $(PRINTF_FLAGS) $(GNL_FLAGS) -o $(NAME)

--------------------------------------------------------------------------------------------






We now go through the next parts of the RULES:
You may have noticed the following:
-@make & -sC.
What are they?
Inside -sC, the "C" part which we shall call "-C" option is used to change the directory
specified by $(LIBFT_SRC_DIR) before executing the make command.
Basically? GO to path e.g."$(LIBFT_SRC_DIR)" and inside make using that make file. 

"-s" makes everything slient. Its not needed but damn it helps to reduce the text 
pollution. Try without it.
I DARE U. GO AHEAD MR JOESTAR.

Ez gg no re.
--------------------------------------------------------------------------------------------
$(LIBFT): 
	@make -sC $(LIBFT_SRC_DIR)
#make -C goes to that path directory's makefile and make using that makefile

$(PRINTF): 
	@make -sC $(PRINTF_SRC_DIR)
	
$(GNL): 
	@make -sC $(GNL_SRC_DIR)

$(MLX_LIB):
	@make -sC $(MLX_DIR)

--------------------------------------------------------------------------------------------







Lastly we have these:
The clean and the fclean section works similar to the one before this.
@make -C goes to the location and "-s" is slient. then we clean or fclean using the 
Makefile's clean or fclean commands.
So if u have any cleaning issue, time to revisit again~.
-Note, just use fclean. solves EVERYTHING-
--------------------------------------------------------------------------------------------
$(OBJ_FILE_PATHS): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c 
	$(CC) -I $(INC_DIR) -c $< -o $@

#Compilation on Linux
%.o: %.c
	$(CC) -I/usr/include -Iminilibx-linux -O3 -c $< -o $@


#Creating rules to compile individual source files for bonus to object files
clean: 
	rm -f $(OBJ_FILE_PATHS) $(GNL_OBJ_FILE_PATHS)
	@make clean -sC $(LIBFT_SRC_DIR)
	@make clean -sC $(PRINTF_SRC_DIR)
	@make clean -sC $(MLX_DIR)

#clear .o files including static library $(NAME)
fclean: clean
	rm -f $(NAME)
	@make fclean -sC $(LIBFT_SRC_DIR)
	@make fclean -sC $(PRINTF_SRC_DIR)
	@make fclean -sC $(GNL_SRC_DIR)
#	@make fclean -sC $(MLX_DIR) Dont need cause the make file no fclean

#clean files and remake "all"
re: fclean all

.PHONY: all clean fclean re
--------------------------------------------------------------------------------------------























Now that the MAKEFILE is done with, we now go to the next best thing~
The programs themselves sighhhhhh.
Btw go to the website 42Docs:
https://harm-smits.github.io/42docs/libs/minilibx.html

This place is a good start to learn how to use minilibx.

Other sources u can refer:
https://reactive.so/post/42-a-comprehensive-guide-to-so_long
https://github.com/pasqualerossi/So_Long/tree/main/game_logic
https://github.com/augustobecker/so_long

==========================================================================================
Notes for later reference:

mlx_init: Initialises the MLX library. Must be called before using any other functions.

mlx_new_window: Creates a new window instance.

mlx_hook: Registers events.

mlx_loop: Loops over the MLX pointer, triggering each hook in order of registration.

mlx_xpm_file_to_image: Converts an XPM file to an MLX image pointer.

mlx_put_image_to_window: Puts your image to the screen at the given coordinates.
//mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y );

mlx_destroy_image: Frees the image.

mlx_destroy_window: Frees the window instance.

mlx_destroy_display: Frees MLX.

mlx_get_data_addr(): returns information about the created image, allowing a user to modify it later.
//mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );

int	mlx_pixel_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color );
/*
The mlx_pixel_put () function draws a defined pixel in the window win_ptr using the (x, y)
coordinates, and the specified color. The origin (0, 0) is the upper left corner of the 
window, the x and y axis respectively pointing right and down.
The connection identifier mlx_ptr is needed.
*/
==========================================================================================






The first thing we have to do is create our so_long.h file so that it can combine with others.
Here is a sample:
Pretty straightforward and simple except for a few things that seems out of norm.

For example, images used for maps and the defining of keys & values.
We use xpm file to create our own images to use for this program. Tons of websites online
that converts png/jpg into xpm so go search for those. 

Type "xpm converter" or something.

As for the defining of keys and the value, that can wait. Technically its not important 
either but man does it help much later to help us tell the difference between the coding.

In this program, using struct is very helpful as we need a lot of programs.
For my case it looks very messy i say so i recommend creating your own ones.
Can use mine as reference.

--------------------------------------------------------------------------------------------
#ifndef SO_LONG_H
# define SO_LONG_H

# include "../other_srcs/libft_project/libft.h"
# include "../other_srcs/printf_project/libftprintf.h"
# include "../other_srcs/get_next_line_project/get_next_line_bonus.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>

//Images used for the maps
# define RICK_XPM "./assets/images/rick.xpm"
# define WALL_XPM "./assets/images/wall.xpm"
# define COIN_XPM "./assets/images/coin.xpm"
# define EXIT_XPM "./assets/images/exit.xpm"
# define EXITOPEN_XPM "./assets/images/exitopen.xpm"
# define PACMAN_XPM "./assets/images/pacman.xpm"

//define the keys
#  define W_KEY 119
#  define S_KEY 115
#  define A_KEY 97
#  define D_KEY 100
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define ESC 65307

//define value
# define WIDTH 100
# define HEIGHT 100
#  define RIGHT 0
#  define LEFT 1
#  define UP 2
#  define DOWN 3

//strut
//wall, collectables, emptyspace.
typedef struct	s_map {
	int		fd;
	int		height;
	int		width;
	int		x;
	int		y;
	int		screen_x;
	int		screen_y;
	int		error_code;
	char	**row;
	char	**grid;
	void	*empty;//for the 0000000000
	void	*wall;//for the 1111111111
	void	*coin;//for the CCCCCCCCCC
	int		coin_exist;
	int		map_coin;// min 1 @ vaildpath
	int		door_exist;// min/max 1 @ vaildpath
	int		wall_check;
	int		player_exist;//min/max 1 @ vaildpath?
	void	*door_exit;//for the EEEEEEEEEE
}				t_map;
//must be in order
typedef struct	s_img {
	int	x;
	int	y;
}				t_img;
//location of player
typedef struct s_player {
	int		size_width;//100
	int		size_height;//100
	int		x;
	int		y;
	int		start_x;
	int		start_y;
	void	*start;// for the P
	void	**location;
	int		steps_taken;
}				t_player;

typedef struct	s_game {
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_map		map;
	t_player	player;
	t_img		img;
	int			score;
	int			moves;
	int			player_position;
	int			img_width;
	int			img_height;
}				t_game;

//from file source
//void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// for colour usage(not important)
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);

//exit_utils.c
void	end_exit(char *message, int exit_code, t_game *game);
void	free_end_exit(char *message, int exit_code, t_game *game, char **str);
void	free_sprites(t_game *game);
void	*game_checkerror_exit(char *message, t_game *game);
int		x_close_window(t_game *game);

//message.c
void	print_message(char *message, int exit_code);

//For mouse & key hooks
int		keyhook(int keycode, t_game *game);
int		mousehook(int keycode, t_game *game);

//invalid.c
void	invalid_checker(t_game *game, char *vaild_char);
void	invalid_window_size(t_game *game);

//map usage?
void	image_testmap(t_game *game);
char	*obtain_str_testmap(t_game *game);
void	xy_testmap(t_game *game);
void	errorcheck_testmap(t_game *game, char **string_map);
void	open_testmap(t_game *game, char *map_path);

//empty.c file
void	background_empty(t_game *game);

//wall.c
void	wall_wall(t_game *game);

//coin.c
void	coin_coin(t_game *game);

//door.c
void	door(t_game *game);

//player.c
void	where_player(t_game *game);
void	find_player(t_game *game);
void	update_position_player(t_game *game, int keycode);

//player_movements.c
void	move_up_movement(t_game *game, int x, int y);
void	move_left_movement(t_game *game, int x, int y);
void	move_down_movement(t_game *game, int x, int y);
void	move_right_movement(t_game *game, int x, int y);
void	put_player(t_game *game, int x, int y);

//vaild_path.c
void	wallcheck_path(t_game *game, int col, int row);
void	playerexit_path(t_game *game, int col, int row);
void	coin_path(t_game *game, int col, int row);
void	new_playerexitcoin_path(t_game *game);
void	check_vaild_path(t_game *game, char ***grid, int x, int y);
void	check_all(t_game *game);


//For (main) windows_so_long use;
void	*init_game(char **argv);
//void	*init_variables();

#endif
/*
#include <unistd.h> // for fork() / execve() / access()
#include <stdio.h> // for printf()
#include <stdlib.h> // exit()
#include <fcntl.h> //open()
#include <sys/wait.h> // wait() / waitpid()
#include <sys/types.h> // for wait() / fork() / pid_t() / wait() / waitpid()
#include <errno.h> // for perror() 
*/
--------------------------------------------------------------------------------------------




-i will not go through the maps.ber or the images i use. Feel free to refer to them through-







Now, @ main_src.
We shallz startz with the first place.
Window_so_long.c

--------------------------------------------------------------------------------------------
Here is my 
ini	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error, not enough arguements");
		return (1);
	}
	else if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".ber", 4))
	{
		ft_printf("File must end with .ber extension.\n");
		return (0);
	}
	init_game(argv);
	return (0);
}


This filled the requirement for the file location and that it must be a 
.ber map.

example, typing:
./so_long "./assets/ber_maps/valid2.ber"

inside the terminal.

--------------------------------------------------------------------------------------------







So eazy u say? Well well well, lets see how u think after this.

Here is how it looks inside init_game(argv):
=============
open_testmap objective is to open the map path that i obtained from argv[1], and 
then reading from the .ber map (using get_next_line). Once i have the map i need to 
check for the following:
-that the map does not have an empty line
-that the map has the following "01CEP". It needs to check that such characters exist
and that no other invalid characters are there.
-that the map does have ALL of those valid characters "01CEP" as checking if there
are invalid are not enough, sometimes the map may not include one valid but all we are
doing is checking if its not valid.

Once we got the map, we add the result into our struct. We need one more as backup for
checking for valid path. By which i mean if its possible to clear the game.
Don't forget to add the width and height into the struct for future uses.
=============


=============
where_player(&game) is used to check the current char "P" to find where it is. If 'p'
does not exist, the game ends.
=============

=============
check_all(&game) @ the window_so_long there checks for all the requirements such as:
-wall '1'
-player 'P'
-coin 'C'
-exit 'E'

(empty '0' is not needed to check)

We need to check if it fills the requirement for the so_long project. Refer to subject
for more details.
Then adding variable values and moving on.
=============

=============
check_valid_path(&game, &game.map.grid, game.player.start_x, game.player.start_y) checks
if it is possible to win the game. For example. I can block the exit with a wall. Should 
the exit be blocked and unable to exit, game will exit cleanly.
=============

=============
new_playerexitcoin_path(&game) checks if there are only 1 player and 1 exit and minimum 1
coin available.
=============

After that, we can do mlx_init();
=============
invalid_window_size(t_game *game) checks if the game window is larger than our window size.
If it is, the program must exit cleanly.
Here u may have valgrind issues so check properly, chances are u tried to destroy the window
display (mlx_new_winow) but it has not come out yet thus will create leaks when all u need to
do is destroy & free mlx_ptr. Check my invalid_window_size @ invalid.c to see how i would free
or destroy the mlx_ptr if it is suppose to exit.
=============

=============
image_testmap(&game) finds the chars respectively and adds the xpm_files with pics.
=============

=============
mlx_key_hook(game.win_ptr, keyhook, &game) is for the keyboard usage, u will need this.
=============

=============
mlx_hook(game.win_ptr, 17, 0, x_close_window, &game) is what u use to close the "x" on the
upper right side of the windows as it is required.
=============

=============
mlx_loop(game.mlx_ptr) keeps the windows going until condition fails.
=============

close(fd) to finish using the map.
--------------------------------------------------------------------------------------------
void	*init_game(char **argv)
{
	t_game		game;

	open_testmap(&game, argv[1]);
	if (game.map.error_code != 0)
		end_exit("open_testmap error @ init_game", 2, &game);
	where_player(&game);
	check_all(&game);
	check_vaild_path(&game, &game.map.grid, game.player.start_x, 
		game.player.start_y);
	new_playerexitcoin_path(&game);
	game.mlx_ptr = mlx_init();
	invalid_window_size(&game);
	image_testmap(&game);
	if (game.map.error_code != 0)
		return (game_checkerror_exit("image_testmap", &game));
	mlx_key_hook(game.win_ptr, keyhook, &game);
	mlx_hook(game.win_ptr, 17, 0, x_close_window, &game);
	mlx_loop(game.mlx_ptr);
	close(game.map.fd);
}

--------------------------------------------------------------------------------------------


