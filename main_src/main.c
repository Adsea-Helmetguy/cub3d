#include "../includes/cub3D.h"
#include <math.h>

void	my_mlx_pixel_put(t_game *game, int x, int y, int color) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlxpixel(game, x, y, color); // put the pixel
}

double	nor_angle(double angle) // normalize the angle
{
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	get_wall_color(t_game *game, double y, int face, int reverse)
		// get the color of the wall
{
	int x;
	double scale;

	scale = game->texture_width / (double)TILE_SIZE;
	if (game->data.flag == 1)
	{
		//x = (int)fmod((game->player.hx * (game->texture_width / TILE_SIZE)),
		//		game->texture_width);
		x = (int)fmod((game->player.hx * scale), game->texture_width);
	}
	else
	{
		//x = (int)fmod((game->player.vy * (game->texture_width / TILE_SIZE)),
		//		game->texture_width);
		x = (int)fmod((game->player.vy * scale), game->texture_width);
	}
	// if (((x_positive(game->player.angle) && !y_positive(game->player.angle))
			// || (!x_positive(game->player.angle)
			// 	&& y_positive(game->player.angle))))
	// 	x *= -1;
	// x = abs(x);
	// printf("hx=%f vy=%f\n",game->player.hx, game->player.vy );
	// x = (int)fmodf((ray *game->texture_size/TILE_SIZE),game->texture_size);
	// if (x > SCREEN_WIDTH / 2 - 500 && x < SCREEN_WIDTH / 2 + 300)
	// 	printf("x: %d y: %f\n", x, y);
	// new add-ons for charles to refer-fixed valgrind-
	// to add bounds check for x & y that they are within "0 to texture_size".
	// if (x <= 0)
	// 	x = 0;
	// if (x >= game->texture_width - 1)
	// 	x = game->texture_width - 1;
	// if (y <= 0)
	// 	y = 0;
	// if (y >= game->texture_height - 1)
	// 	y = game->texture_height - 1;
	x = ((int)(x * reverse) % game->texture_width + game->texture_width) % game->texture_width;

	//int y_tex;//(for rescaling purposes charles)
	//double scale2;

	//scale2 = game->texture_height / (double)TILE_SIZE;
	//y_tex = (int)fmod((y * scale2), game->texture_height);
	return (game->textures[face][(int)y * game->texture_width + (int)x]);//game->texture_size is it height or width
}

int	px_color(double angle, double px, double wall_height, t_game *game)
		// get the color of the wall
{
	double y;

	y = (px - ((SCREEN_HEIGHT - wall_height) / 2)) / wall_height
		* game->texture_height;//game->texture_size is it height or width
	angle = nor_angle(angle); // normalize the angle
	if (px < (SCREEN_HEIGHT - wall_height) / 2)
		return (0x89CFF3FF); // ceiling
	else if (px > (SCREEN_HEIGHT + wall_height) / 2)
		return (0x000000FF); // floor
	else
	{
		if (game->data.flag == 0)
		{
			if (angle > M_PI / 2 && angle < 3 * (M_PI / 2))
				return (get_wall_color(game, y, WEST, -1)); // west wall
			else
				return (get_wall_color(game, y, EAST, 1)); // east wall
		}
		else
		{
			if (angle > 0 && angle < M_PI)
				return (get_wall_color(game, y, SOUTH, -1)); // south wall
			else
				return (get_wall_color(game, y, NORTH, 1)); // north wall
		}
	}
}

void	render(t_game *game, int ray, double angle) // render the wall
{
	double wall_height;
	double px;

	game->data.distance *= cos(nor_angle(angle - game->player.angle));
	wall_height = ((SCREEN_WIDTH / 2) / tan(game->data.radfov / 2) * (TILE_SIZE
				/ game->data.distance));
	if (game->data.distance == 0 || wall_height == INFINITY || wall_height == \
		-INFINITY)
		wall_height = SCREEN_HEIGHT;
	px = 0;
	while (px < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, ray, px, px_color(angle, px, wall_height, game));
		px++;
	}
}

int	x_positive(double angle) // facing right true facing left false
{
	if (angle >= M_PI / 2 && angle <= 3 * (M_PI / 2))
		return (0);
	return (1);
}

int	y_positive(double angle) // facing down true facing up false
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int	has_wall_at(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= game->data.map_w * TILE_SIZE || y < 0
		|| y >= game->data.map_h * TILE_SIZE)
		return (1);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_x >= game->data.map_w
		|| map_y >= game->data.map_h)
		return (1);
	if (game->data.map2d[map_y][map_x] == '1')
		return (1);
	return (0);
}

double	v_collision(t_game *game, double angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	int		adjust;

	adjust = 0;
	x_intercept = game->player.pixel_x - (game->player.pixel_x % TILE_SIZE);
		// floor(game->player.pixel_x / TILE_SIZE) * TILE_SIZE;
	x_step = TILE_SIZE;
	if (x_positive(angle))
		x_intercept += TILE_SIZE;
	else
	{
		adjust = -1;
		x_step = -TILE_SIZE;
	}
	y_intercept = game->player.pixel_y + (x_intercept - game->player.pixel_x)
		* tan(angle);
	if (angle == 0 || angle == M_PI)
		return (SCREEN_HEIGHT);
	y_step = TILE_SIZE * tan(angle);
	if ((!y_positive(angle) && y_step > 0) || (y_positive(angle) && y_step < 0))
		y_step *= -1;
	while (!has_wall_at(game, x_intercept + adjust, y_intercept))
	{
		x_intercept += x_step;
		y_intercept += y_step;
	}
	game->player.vx = x_intercept;
	game->player.vy = y_intercept;
	return (distance(game->player.pixel_x, game->player.pixel_y, x_intercept,
			y_intercept));
}

double	h_collision(t_game *game, double angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	int		adjust;

	adjust = 0;
	// printf("angle: %f tan angle:%f \n", angle, tan(angle));
	y_intercept = game->player.pixel_y - (game->player.pixel_y % TILE_SIZE);
		// floor(game->player.pixel_y / TILE_SIZE) * TILE_SIZE;
	y_step = TILE_SIZE;
	if (y_positive(angle))
		y_intercept += TILE_SIZE;
	else
	{
		adjust = -1;
		y_step = -TILE_SIZE;
	}
	x_intercept = game->player.pixel_x + ((y_intercept - game->player.pixel_y)
			/ tan(angle));
	if (angle == M_PI / 2 || angle == 3 * (M_PI / 2))
		return (SCREEN_WIDTH);
	x_step = TILE_SIZE / tan(angle);
	if ((!x_positive(angle) && x_step > 0) || (x_positive(angle) && x_step < 0))
		x_step *= -1;
	while (!has_wall_at(game, x_intercept, y_intercept + adjust))
	{
		x_intercept += x_step;
		y_intercept += y_step;
	}
	game->player.hx = x_intercept;
	game->player.hy = y_intercept;
	return (distance(game->player.pixel_x, game->player.pixel_y, x_intercept,
			y_intercept));
}

void	drawrayonmap(t_game *game, double angle, double distance)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;

	// printf("angle: %f distance: %f\n", angle, distance);
	x = game->player.pixel_x;
	y = game->player.pixel_y;
	x_step = cos(angle) * 5;
	y_step = sin(angle) * 5;
	while (distance > 0)
	{
		my_mlx_pixel_put(game, x, y, 0x00FF0000);
		x += x_step;
		y += y_step;
		distance -= 5;
	}
}

void	raycasting(t_game *game)
{
	double	h_col;
	double	v_col;
	double	angle;
	double	increment;
	int		ray;

	ray = 0;
	angle = nor_angle(game->player.angle - (game->data.radfov / 2));
	// printf("pixel x: %d pixel y: %d angle:%f \n", game->player.pixel_x,
		// game->player.pixel_y, angle);
	increment = (double)game->data.radfov / (double)SCREEN_WIDTH;
	// while (angle < nor_angle(game->player.angle + (FOV_ANGLE / 2)))
	while (ray < SCREEN_WIDTH)
	{
		game->data.flag = 0;
		// printf("angle: %f increment: %f\n", angle, increment);
		h_col = h_collision(game, angle);
		v_col = v_collision(game, angle);
		// printf("angle:%f h_col: %f v_col: %f\n",angle,h_col, v_col);
		if (h_col < v_col)
		{
			game->data.distance = h_col;
			game->data.flag = 1;
		}
		else
		{
			game->data.distance = v_col;
		}
		// printf("distance: %f\n", game->data.distance);
		// drawrayonmap(game, angle, game->data.distance);
		render(game, ray, angle); // render the wall
		ray++;                    // next ray
		angle += increment;
		angle = nor_angle(angle);
	}
}

int	gameplay(t_game *game)
{
	raycasting(game);
	// cast_rays(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}

static void	starting_view(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!(game->mlx.mlx_ptr))
	{
		game->error_code = 1;
		return ;
	}
	setup_texture(game); // draw texture here && fail if no texture found
	window_screen_creation(game);
	mlxpixel_on_screen(game);
}

static void	starting_game(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 17, 1L << 17, x_close_window, game);
	mlx_hook(game->mlx.win_ptr, 02, 1L << 0, keyhook, game);
	mlx_hook(game->mlx.win_ptr, 03, 1L << 1, keyhook_release, game);
	// gameplay(game);
	mlx_loop_hook(game->mlx.mlx_ptr, &gameplay, game);
}

int	start_the_game(char **argv)
{
	t_game	game;

	init_variables(&game);
	open_testmap(&game, argv[1]);
	init_variable_player(&game);
	printf("map w: %i, map h: %i\n", game.data.map_w, game.data.map_h);
	starting_view(&game); // mlx_init is here
	if (game.error_code != 0)
		return (game_checkerror_exit("cub3d testmap", &game));
	starting_game(&game); // gameplay is here!
	// if (game.error_code != 0)
	//	return (game_checkerror_exit("image_testmap", &game));
	mlx_loop(game.mlx.mlx_ptr);
	// free_gameloop_end("Quitting game.\n", 0, &game);
		//free the element_values()
	free_before_game("Quitting game.\n", 0, &game); // free the element_values()
	return (0);
}

//./cub3D ./map/maplocation (only 1 argument)
// e.g make re && ./cub3D assets/cub_maps/valid_cub/valid3.cub
// e.g make re && ./cub3D assets/cub_maps/invalid_cub/invalid1.cub
// e.g make re && ./cub3D assets/cub_maps/invalid_cub/invalid7.cub
// e.g //make re && valgrind --leak-check=full --show-leak-kinds=all ./cub3D assets/cub_maps/invalid_cub/invalid1.cub
//(success!)
// use this:
// https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error, not enough arguments");
		return (1);
	}
	else if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4))
	{
		printf("File must end with \".cub\" extension.\n");
		return (0);
	}
	printf("\n-----------\nSuccess! It is a \".cub\" file!!!\n-----------\n");
	if (start_the_game(argv))
		return (1);
	return (0);
}
