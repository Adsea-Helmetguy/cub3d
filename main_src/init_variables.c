/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:59:13 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 16:48:06 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_variables(t_game *game)
{
	game->screen_x = 0;
	game->screen_y = 0;
	game->error_code = 0;
	game->data.map2d = NULL;
	game->player.p_x = 0;
	game->player.p_y = 0;
	game->data.map_w = 0;
	game->data.map_h = 0;
	game->data.fd = 0;
	game->data.radfov = FOV_ANGLE * M_PI / 180;
	game->elements.north_texture = NULL;
	game->elements.south_texture = NULL;
	game->elements.west_texture = NULL;
	game->elements.east_texture = NULL;
	game->player.pixel_x = 0;
	game->player.pixel_y = 0;
	game->player.angle = 270 * M_PI / 180;
	init_variables2(game);
}

void	init_variables2(t_game *game)
{
	int	face;

	game->mlx.addr = NULL;
	game->mlx.bits_per_pixel = 0;
	game->mlx.line_length = 0;
	game->mlx.endian = 0;
	game->key.w_pressed = 0;
	game->key.a_pressed = 0;
	game->key.s_pressed = 0;
	game->key.d_pressed = 0;
	game->key.left_rotate = 0;
	game->key.right_rotate = 0;
	face = 0;
	while (face < 4)
	{
		game->texture_width[face] = 0;
		game->texture_height[face] = 0;
		face++;
	}
}

void	init_variable_player(t_game *game)
{
	game->player.pixel_x = game->player.p_x * TILE_SIZE + TILE_SIZE / 2;
	game->player.pixel_y = game->player.p_y * TILE_SIZE + TILE_SIZE / 2;
	if (game->data.map_h == 0 || game->data.map_w == 0)
		game->error_code = 1;
	else
		game->error_code = 0;
}
