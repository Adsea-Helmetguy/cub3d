/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:57:56 by mlow              #+#    #+#             */
/*   Updated: 2024/07/15 16:59:13 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
//
//
/*
int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window (mlx_ptr, 300, 300, "Hello World");
	if (!win_ptr)
		return (2);
	mlx_loop(mlx_ptr);
	return (0);
}
*/
