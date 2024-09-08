/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:57:56 by mlow              #+#    #+#             */
/*   Updated: 2024/08/17 18:15:21 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
# include <math.h>

void my_mlx_pixel_put(t_game *game, int x, int y, int color) // put the pixel
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
	// mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, color); // put the pixel
}

double toradian(double angle)
{
	return (angle * (M_PI / 180));
}

double nor_angle(double angle) // normalize the angle
{
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
 int  i;

	i = b_pix;
	while (i < SCREEN_HEIGHT)
	{
		// printf("i: %d\n", i);
		// printf("ray: %d\n", ray);
		// printf("0x00ffffff\n");
		my_mlx_pixel_put(game, ray, i++, 0xB99470FF); // floor
	}
	i = 0;
	while (i < t_pix)
	{
		// printf("i: %d\n", i);
		// printf("ray: %d\n", ray);
		// printf("0x89CFF3FF\n");
		my_mlx_pixel_put(game, ray, i++, 0x89CFF3FF); // ceiling
	}
}

int get_color(double angle, int flag) // get the color of the wall
{
	angle = nor_angle(angle); // normalize the angle
	if (flag == 0)
	{
		if (angle > 90 && angle < 3 * (90))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (angle > 0 && angle < 180)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void draw_wall(t_game *game, int ray, int t_pix, int b_pix, int flag, double angle) // draw the wall
{
	int color;

	color = get_color(flag, angle);
	while (t_pix < b_pix)
		my_mlx_pixel_put(game, ray, t_pix++, color);
}

void render_wall(t_game *game, int ray, double angle) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

	// t_mlx *mlx = &game->mlx;
	game->data.distance *= cos(nor_angle(angle - toradian(game->player.angle))); // fix the fisheye
	wall_h = (TILE_SIZE / game->data.distance) * ((SCREEN_WIDTH / 2) / tan(toradian(FOV_ANGLE / 2))); // get the wall height
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > SCREEN_HEIGHT) // check the bottom pixel
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(game, ray, t_pix, b_pix, game->data.flag, angle); // draw the wall
	draw_floor_ceiling(game, ray, t_pix, b_pix); // draw the floor and the ceiling
}

int x_positive(double angle) //facing right true facing left false
{
	if (angle >= M_PI / 2 && angle <= 3 * (M_PI / 2))
		return (0);
	return (1);
}

int y_positive(double angle) //facing down true facing up false
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

int distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int has_wall_at(t_game *game, double x, double y)
{
	int map_x;
	int map_y;

	if (x < 0 || x >= game->data.map_w * TILE_SIZE || y < 0 || y >= game->data.map_h * TILE_SIZE)
		return (1);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (game->data.map2d[map_y][map_x] == '1')
		return (1);
	return (0);
}

double v_collision(t_game *game, double angle)
{
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	int    adjust;
	
	adjust = 0;
	x_intercept = game->player.pixel_x - (game->player.pixel_x % TILE_SIZE); //floor(game->player.pixel_x / TILE_SIZE) * TILE_SIZE;
	if (x_positive(angle))
		x_intercept += TILE_SIZE;
	y_intercept = game->player.pixel_y + (x_intercept - game->player.pixel_x) * tan(angle);
	x_step = TILE_SIZE;
	if (!x_positive(angle))
		x_step *= -1;
	if (!x_positive(angle))
		adjust = -1;
	y_step = TILE_SIZE * tan(angle);
	if ((!y_positive(angle) && y_step > 0) || (y_positive(angle) && y_step < 0))
		y_step *= -1;
	while (x_intercept >= 0 && x_intercept <= game->data.map_w * TILE_SIZE && y_intercept >= 0 && y_intercept <= game->data.map_h * TILE_SIZE)
	{
		if (has_wall_at(game, x_intercept + adjust, y_intercept))
			return (distance(game->player.pixel_x, game->player.pixel_y, x_intercept, y_intercept));
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return (INT_MAX);
}

double h_collision(t_game *game, double angle)
{
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	int 	adjust;

	adjust = 0;
	printf("angle: %f tan angle:%f \n", angle, tan(angle));
	y_intercept = game->player.pixel_y - (game->player.pixel_y % TILE_SIZE); //floor(game->player.pixel_y / TILE_SIZE) * TILE_SIZE;
	if (y_positive(angle))
		y_intercept += TILE_SIZE;
	x_intercept = game->player.pixel_x + ((y_intercept - game->player.pixel_y) / tan(angle));
	y_step = TILE_SIZE;
	if (!y_positive(angle))
		y_step *= -1;
	if (!y_positive(angle))
		adjust = -1;
	x_step = TILE_SIZE / tan(angle);
	if ((!x_positive(angle) && x_step > 0) || (x_positive(angle) && x_step < 0))
		x_step *= -1;
	while (x_intercept >= 0 && x_intercept <= game->data.map_w * TILE_SIZE && y_intercept >= 0 && y_intercept <= game->data.map_h * TILE_SIZE)
	{
		if (has_wall_at(game, x_intercept, y_intercept + adjust))
			return (distance(game->player.pixel_x, game->player.pixel_y, x_intercept, y_intercept));
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return (INT_MAX);
}

void drawrayonmap(t_game *game, double angle, double distance)
{
	double x;
	double y;
	double x_step;
	double y_step;

	printf("angle: %f distance: %f\n", angle, distance);

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

void raycasting(t_game *game)
{
	double h_col;
	double v_col;
	double angle;
	double increment;
	int ray;

	ray= 0;
	angle = nor_angle(toradian(game->player.angle) - toradian(FOV_ANGLE / 2));
	increment = toradian((double)FOV_ANGLE / (double)SCREEN_WIDTH);

	// while (angle < nor_angle(game->player.angle + (FOV_ANGLE / 2)))
	while (ray < SCREEN_WIDTH)
	{
		// printf("angle: %f increment: %f\n", angle, increment);
		h_col = h_collision(game, angle);
		v_col = v_collision(game, angle);
		printf("angle:%f h_col: %f v_col: %f\n",angle,h_col, v_col);
		if (h_col < v_col)
		{
			game->data.distance = h_col;
		}
		else
		{
			game->data.distance = v_col;
			game->data.flag = 1;
		}
		// printf("distance: %f\n", game->data.distance);
		// drawrayonmap(game, angle, game->data.distance);
		render_wall(game, ray, angle); // render the wall
		ray++; // next ray
		angle += increment;
		angle = nor_angle(angle);
	}
}

int gameplay(t_game *game)
{
	// mlx_delete_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	// mlx_delete_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	raycasting(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img_ptr, 0, 0);
	return (0);
}

int	start_the_game(char **argv)
{
	t_game		game;

	init_variables(&game);
	//check game first before doing the mlx, look at notion map creation!
	//https://www.notion.so/How-to-do-the-map-5a032dfe0f5549139bbd458b021a3175
	open_testmap(&game, argv[1]);
	init_variable_player(&game);
//
//game start!!
	game.mlx.mlx_ptr = mlx_init();
	if (!(game.mlx.mlx_ptr))
		return (1);
	invalid_window_size_checker(&game);
	game.mlx.img_ptr = mlx_new_image(game.mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	//Now, we have an image but no pixels
	game.mlx.addr = mlx_get_data_addr(game.mlx.img_ptr, &game.mlx.bits_per_pixel,
				&game.mlx.line_length, &game.mlx.endian);
	mlxpixel_on_screen(&game);
	//mlximage_on_screen(&game);//new add-on for the xpm.files
	if (game.error_code != 0)
		return (game_checkerror_exit("image_testmap", &game));
//
//
	//mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);
	// game loop continuously call a specified function to update the game state and render the frames.
	gameplay(&game);
	// mlx_loop_hook(game.mlx.mlx_ptr, &gameplay, &game);
	mlx_key_hook(game.mlx.win_ptr, keyhook, &game);
	mlx_hook(game.mlx.win_ptr, 17, 0, x_close_window, &game);
	mlx_loop(game.mlx.mlx_ptr);
	close(game.data.fd);
	//free the element_values()
	free_end_exit("just for valgrind\n", 0, &game, NULL);
	return (0);
}

//./cub3D ./map/maplocation (only 1 argument)
//e.g make re && ./cub3D assets/cub_maps/valid_cub/valid3.cub
//e.g make re && ./cub3D assets/cub_maps/invalid_cub/invalid1.cub
//e.g make re && ./cub3D assets/cub_maps/invalid_cub/invalid7.cub
//e.g //make re && valgrind --leak-check=full --show-leak-kinds=all ./cub3D assets/cub_maps/invalid_cub/invalid1.cub
//(success!)
//use this:
//https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf
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
