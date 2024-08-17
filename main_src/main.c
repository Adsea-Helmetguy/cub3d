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

double h_collision(t_game *game, double angle)
{
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	double x_check;
	double y_check;

	y_intercept = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += game->player.is_facing_down ? TILE_SIZE : 0;
	x_intercept = game->player.x + (y_intercept - game->player.y) / tan(angle);
	y_step = TILE_SIZE;
	y_step *= game->player.is_facing_up ? -1 : 1;
	x_step = TILE_SIZE / tan(angle);
	x_step *= (game->player.is_facing_left && x_step > 0) ? -1 : 1;
	x_step *= (game->player.is_facing_right && x_step < 0) ? -1 : 1;
	x_check = x_intercept;
	y_check = y_intercept;
	while (x_check >= 0 && x_check <= game->data.map_w * TILE_SIZE && y_check >= 0 && y_check <= game->data.map_h * TILE_SIZE)
	{
		if (has_wall_at(game, x_check, y_check))
			return (distance(game->player.x, game->player.y, x_check, y_check));
		x_check += x_step;
		y_check += y_step;
	}
	return (INT_MAX);
}

void raycasting(t_game *game)
{
	double h_col;
	double v_col;
	double angle;

	angle = game->player.angle - (FOV_ANGLE / 2);
	while (angle < game->player.angle + (FOV_ANGLE / 2))
	{
		h_col = h_collision(game, angle);
		v_col = v_collision(game, angle);
		if (h_col < v_col)
		{
			//draw vertical line
		}
		else
		{
			//draw horizontal line
		}
		angle += (FOV_ANGLE / SCREEN_WIDTH);
	}
}

int gameplay(t_game *game)
{
	raycasting(game);
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
	mlxpixel_on_screen(&game);
	//mlximage_on_screen(&game);//new add-on for the xpm.files
	if (game.error_code != 0)
		return (game_checkerror_exit("image_testmap", &game));
//
//these two needs fixing
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
