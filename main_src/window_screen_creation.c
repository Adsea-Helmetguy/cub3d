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

void	window_screen_creation(t_game *game)
{
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT, "testmap");
	game->data.map_w_in_pixels = (double)SCREEN_WIDTH;
	game->data.map_h_in_pixels = (double)SCREEN_HEIGHT;
}
