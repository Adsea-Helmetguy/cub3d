/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:03:45 by mlow              #+#    #+#             */
/*   Updated: 2023/12/06 00:20:26 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
void	free_sprites(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->map.coin);
	mlx_destroy_image(game->mlx_ptr, game->map.wall);
	mlx_destroy_image(game->mlx_ptr, game->player.start);
	mlx_destroy_image(game->mlx_ptr, game->map.empty);
	mlx_destroy_image(game->mlx_ptr, game->map.door_exit);
}
*/

int	x_close_window(t_game *game)
{
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	//if (game->mlx.mlx_ptr)
	//	mlx_destroy_display(game->mlx.mlx_ptr);
	free(game->mlx.mlx_ptr);
	free_gameloop_end("Quitting game.\n", 0, game);
	//end_exit("Quitting game.\n", 0, game);
	return (0);
}

int	game_checkerror_exit(char *message, t_game *game)
{
	if (game->error_code != 0)
	{
		printf("ERROR!! ");
		printf("%s", message);
		printf(" error_code != 0\n");
	}
	return (1);
}