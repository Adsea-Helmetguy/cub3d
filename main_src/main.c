/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:57:56 by mlow              #+#    #+#             */
/*   Updated: 2024/09/03 16:25:53 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_texture_img(t_game *game, t_img *tmp, char *path)
{
	tmp->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path,
			&(game->texture_size), &(game->texture_size));
	//if (image->img == NULL)
	//	exit_and_free(data, error_msg(ERR_MLX_IMG, 21));
	tmp->addr = (int *)mlx_get_data_addr(tmp->img, &tmp->pixel_bits,
			&tmp->size_line, &tmp->endian);
	return ;
}


static int	*xpm_to_img(t_game *game, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(game, &tmp, path);//tmp is updated here to be used
//	buffer = ft_calloc(1,
//			sizeof * buffer * data->texture_det.size * data->texture_det.size);
	buffer = malloc(sizeof(int) * (game->texture_size * game->texture_size));
	//if (!buffer)
	//	exit_and_free(data, error_msg(ERR_MALC, 25));
	y = 0;
	while (y < game->texture_size)
	{
		x = 0;
		while (x < game->texture_size)
		{
			buffer[y * game->texture_size + x]
				= tmp.addr[y * game->texture_size + x];
			++x;
		}
		y++;
	}
	//mlx_destroy_image(data->view.mlx, tmp.img);
	return (buffer);
}

static void	setup_texture(t_game *game)
{
	game->textures = malloc(sizeof(int *) * 5);
	//if (!data->textures)
	//	exit_and_free;
	game->texture_size = 225;//cause my textures are 225 in size
	//north=0,south=1,east=2,west=3,final=null;
	game->textures[NORTH] = xpm_to_img(game, game->elements.north_texture);
	game->textures[SOUTH] = xpm_to_img(game, game->elements.south_texture);
	game->textures[EAST] = xpm_to_img(game, game->elements.east_texture);
	game->textures[WEST] = xpm_to_img(game, game->elements.west_texture);
	game->textures[5] = NULL;
}

static void	starting_view(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!(game->mlx.mlx_ptr))
	{
		game->error_code = 1;
		return ;
	}
	setup_texture(game);//draw texture here
	player_set_direction(game);
	window_screen_creation(game);
	mlxpixel_on_screen(game);
}

static void	starting_game(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 17, 1L<<17, closehook, game);
	mlx_hook(game->mlx.win_ptr, 02, 1L<<0, keyhook, game);
	mlx_hook(game->mlx.win_ptr, 03, 1L<<1, keyhook_release, game);
	mixpixel_render(game);
	//mlx_loop_hook(game->mlx.mlx_ptr, mixpixel_render, game);
}

int	start_the_game(char **argv)
{
	t_game		game;

	init_variables(&game);
	open_testmap(&game, argv[1]);
	init_variable_player(&game);
//
//game start!!
	starting_view(&game);//mlx_init is here
	if (game.error_code != 0)
		return (game_checkerror_exit("cub3d testmap", &game));
	starting_game(&game);
	mlx_hook(game.mlx.win_ptr, 17, 0, x_close_window, &game);
	mlx_loop(game.mlx.mlx_ptr);
	close(game.data.fd);
	//free the element_values() here
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
//check game first before doing the mlx, look at notion map creation!
//https://www.notion.so/How-to-do-the-map-5a032dfe0f5549139bbd458b021a3175
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
