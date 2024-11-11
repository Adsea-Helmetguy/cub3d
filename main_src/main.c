/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:30:54 by cwijaya           #+#    #+#             */
/*   Updated: 2024/11/11 18:32:36 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <math.h>

int	gameplay(t_game *game)
{
	raycasting(game);
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
	setup_texture(game);
	window_screen_creation(game);
	mlxpixel_on_screen(game);
}

static void	starting_game(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 17, 1L << 17, x_close_window, game);
	mlx_hook(game->mlx.win_ptr, 02, 1L << 0, keyhook, game);
	mlx_hook(game->mlx.win_ptr, 03, 1L << 1, keyhook_release, game);
	mlx_loop_hook(game->mlx.mlx_ptr, &gameplay, game);
}

int	start_the_game(char **argv)
{
	t_game	game;

	init_variables(&game);
	open_testmap(&game, argv[1]);
	init_variable_player(&game);
	printf("map w: %i, map h: %i\n", game.data.map_w, game.data.map_h);
	starting_view(&game);
	if (game.error_code != 0)
		return (game_checkerror_exit("cub3d testmap", &game));
	starting_game(&game);
	if (game.error_code != 0)
		return (game_checkerror_exit("image_testmap", &game));
	mlx_loop(game.mlx.mlx_ptr);
	return (0);
}

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
