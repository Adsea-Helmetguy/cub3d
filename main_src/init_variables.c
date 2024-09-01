/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:59:13 by mlow              #+#    #+#             */
/*   Updated: 2024/08/31 15:53:25 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//what are the things we need for the game to work.
void	init_variables(t_game *game)
{
	game->screen_x = 0;
	game->screen_y = 0;
	game->error_code = 0;
	//game->data->map2d = malloc(sizeof(char *) * (h_map));
	game->error_code = 0;
	game->data.map2d = NULL;
	game->data.p_x = 0;
	game->data.p_y = 0;
	game->data.map_w = 0;
	game->data.map_h = 0;
	game->data.map_w_in_pixels = 0;
	game->data.map_h_in_pixels = 0;
	game->data.fd = 0;
	//elements
	game->elements.north_texture = NULL;
	game->elements.south_texture = NULL;
	game->elements.west_texture = NULL;
	game->elements.east_texture = NULL;
	//for player
	game->player.pixel_x = 0;
	game->player.pixel_y = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	//game->player.plane_x = 0;
	//game->player.plane_y = 0;
	game->player.sidedir_x = 0;
	game->player.sidedir_y= 0;
	game->player.step_x = 0;
	game->player.step_y = 0;
	game->player.rotation = 0;
	game->player.left_right = 0;
	game->player.up_down = 0;
	game->player.angle = 0;
	game->player.fov_rd = 0;
	//for raycasting
	game->ray.camera_x = 0;
	game->ray.dir_x = 0;
	game->ray.dir_y = 0;
	game->ray.map_w = 0;
	game->ray.map_h = 0;
	game->ray.deltadist_x = 0;
	game->ray.deltadist_y = 0;
	game->ray.hit_side = 0;
	//for key.c
	game->key.w_pressed = 0;
	game->key.a_pressed = 0;
	game->key.s_pressed = 0;
	game->key.d_pressed = 0;
	game->key.left_rotate = 0;
	game->key.right_rotate = 0;
	//game->key.toggle_state = 0;
	//for mlx
	game->mlx.mlx_ptr = NULL;
	game->mlx.win_ptr = NULL;
	game->mlx.img_ptr = NULL;
	game->mlx.addr = NULL;
	game->mlx.bits_per_pixel = 0;
	game->mlx.line_length = 0;
	game->mlx.endian = 0;
}

void	init_variable_player(t_game *game)
{
	game->player.pixel_x = game->data.p_x * TILE_SIZE + TILE_SIZE / 2;
	game->player.pixel_y = game->data.p_y * TILE_SIZE + TILE_SIZE / 2;
	//"+ TILE_SIZE / 2" is to centre our player in the centre of the title.
	printf("player width: %f\nplayer height: %f\n", game->player.pixel_x, game->player.pixel_y);
	//player field of view and angle
	//game->player.fov_rd = (FOV * M_PI) / 180;
	//game->player.angle = M_PI;
	if (game->data.map_h == 0 || game->data.map_w == 0)
		game->error_code = 1;
	else
		game->error_code = 0;
	game->ray.map_w = 0;
	game->ray.map_h = 0;
}
