/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:16:47 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 18:35:39 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	window_screen_creation(t_game *game)
{
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3d");
	if (!(game->mlx.win_ptr))
	{
		game->error_code = 1;
		return ;
	}
	game->data.map_w_in_pixels = (double)SCREEN_WIDTH;
	game->data.map_h_in_pixels = (double)SCREEN_HEIGHT;
}
