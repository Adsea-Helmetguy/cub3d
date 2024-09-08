/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:59:13 by mlow              #+#    #+#             */
/*   Updated: 2024/08/10 18:32:35 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_variables(t_game *game)
{
	//what are the things we need for the game to work?
	game->screen_x = 0;
	game->screen_y = 0;
	game->error_code = 0;
	//game->data->map2d = malloc(sizeof(char *) * (h_map));
	game->error_code = 0;
	game->data.map2d = NULL;
	game->player.p_x = 0;
	game->player.p_y = 0;
	game->data.map_w = 0;
	game->data.map_h = 0;
	game->data.fd = 0;
	game->data.radfov = FOV_ANGLE * M_PI / 180;
	//elements
	game->elements.north_texture = NULL;
	game->elements.south_texture = NULL;
	game->elements.west_texture = NULL;
	game->elements.east_texture = NULL;
	//for player
	game->player.pixel_x = 0;
	game->player.pixel_y = 0;
	game->player.angle = 90 * M_PI / 180;
	//for mlx
	game->mlx.addr = NULL;
	game->mlx.bits_per_pixel = 0;
	game->mlx.line_length = 0;
	game->mlx.endian = 0;
}

void	init_variable_player(t_game *game)
{
	game->player.pixel_x = game->player.p_x * TILE_SIZE + TILE_SIZE / 2;
	game->player.pixel_y = game->player.p_y * TILE_SIZE + TILE_SIZE / 2;
	//"+ TILE_SIZE / 2" is to centre our player in the centre of the title.
	printf("player width: %d\nplayer height: %d\n", game->player.pixel_x, game->player.pixel_y);
	//player field of view and angle
	//game->player.fov_rd = (FOV * M_PI) / 180;
	//game->player.angle = M_PI;
	if (game->data.map_h == 0 || game->data.map_w == 0)
		game->error_code = 1;
	else
		game->error_code = 0;
}
