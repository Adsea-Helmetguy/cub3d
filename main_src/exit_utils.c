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

int	x_close_window(t_game *game)
{
//	int	array;
/*
	array = -1;
	if (game->map.row)
	{
		while (game->map.row[++array])
			free(game->map.row[array]);
		free(game->map.row);
	}
	array = -1;
	if (game->map.grid)
	{
		while (game->map.grid[++array])
			free(game->map.grid[array]);
		free(game->map.grid);
	}
	//free_sprites(game);
*/
	mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_destroy_display(game->mlx.mlx_ptr);
	free(game->mlx.mlx_ptr);
	return (0);
}

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
