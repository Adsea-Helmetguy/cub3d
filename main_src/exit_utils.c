/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:03:45 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 17:33:39 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	x_close_window(t_game *game)
{
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
	free_gameloop_end("Quitting game.\n", 0, game);
	return (0);
}

int	close_window_invalidtextures(t_game *game)
{
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
	free(game->textures);
	free_before_game("UNABLE TO FIND TEXTURES!\n", -1, game);
	return (0);
}

int	game_checkerror_exit(char *message, t_game *game)
{
	if (game->error_code != 0)
	{
		printf("ERROR!! ");
		printf("%s", message);
		printf(" error_code != 0\n");
		free_before_game("Quitting game.\n", 0, game);
	}
	return (1);
}

int	tmp_error_exit(char *message, t_game *game, char ***tmp_map2)
{
	if (game->error_code != 0)
	{
		printf("ERROR!! ");
		printf("%s", message);
		printf(" error_code != 0\n");
		if (*tmp_map2)
			ftps_free(*tmp_map2);
		free_before_game("Quitting game.\n", 0, game);
	}
	return (1);
}
