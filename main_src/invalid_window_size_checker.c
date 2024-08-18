/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_window_size_checker.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:53:44 by mlow              #+#    #+#             */
/*   Updated: 2024/08/10 19:53:57 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	invalid_window_size_checker(t_game *game)
{
	int	window_x;
	int	window_y;

	// window_x = game->data.map_w * TILE_SIZE;
	// window_y = game->data.map_h * TILE_SIZE;
	window_x = SCREEN_WIDTH;
	window_y = SCREEN_HEIGHT;
	game->screen_x = 0;
	game->screen_y = 0;
	mlx_get_screen_size(game->mlx.mlx_ptr, &game->screen_x, 
		&game->screen_y);
	if (window_x > game->screen_x || window_y > game->screen_y)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
		end_exit("Map size is too large.\n", 2, game);
	}
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, window_x,
			window_y, "testmap");
}
