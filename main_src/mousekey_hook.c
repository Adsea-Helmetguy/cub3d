/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousekey_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:48:30 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 18:36:00 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	keyhook_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->key.w_pressed = 0;
	if (keycode == A_KEY)
		game->key.a_pressed = 0;
	if (keycode == S_KEY)
		game->key.s_pressed = 0;
	if (keycode == D_KEY)
		game->key.d_pressed = 0;
	if (keycode == LEFT_KEY)
		game->key.left_rotate = 0;
	if (keycode == RIGHT_KEY)
		game->key.right_rotate = 0;
	return (0);
}

void	rotate_player(t_game *game, int i)
{
	if (i == 1)
	{
		game->player.angle += ROTATE_SPEED;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	else
	{
		game->player.angle -= ROTATE_SPEED;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
}

void	move_player(t_game *game, double move_x, double move_y)
{
	int	map_grid_y;
	int	map_grid_x;
	int	new_x;
	int	new_y;

	new_x = roundf(game->player.pixel_x + move_x);
	new_y = roundf(game->player.pixel_y + move_y);
	map_grid_x = ((new_x + 10) / TILE_SIZE);
	map_grid_y = ((new_y + 10) / TILE_SIZE);
	if (game->data.map2d[map_grid_y][map_grid_x] != '1'
		&& game->data.map2d[(int)((new_y - 10) / TILE_SIZE)][(int)((new_x - 10)
			/ TILE_SIZE)] != '1'
		&& game->data.map2d[map_grid_y][game->player.pixel_x / TILE_SIZE] != '1'
		&& game->data.map2d[game->player.pixel_y
		/ TILE_SIZE][map_grid_x] != '1')
	{
		game->player.pixel_x = new_x;
		game->player.pixel_y = new_y;
	}
}

void	khook(t_game *game, double move_x, double move_y)
{
	if (game->key.right_rotate == 1)
		rotate_player(game, 1);
	if (game->key.left_rotate == 1)
		rotate_player(game, 0);
	if (game->key.d_pressed == 1)
	{
		move_x = -sin(game->player.angle) * MOVE_SPEED;
		move_y = cos(game->player.angle) * MOVE_SPEED;
	}
	if (game->key.a_pressed == 1)
	{
		move_x = sin(game->player.angle) * MOVE_SPEED;
		move_y = -cos(game->player.angle) * MOVE_SPEED;
	}
	if (game->key.w_pressed == 1)
	{
		move_x = cos(game->player.angle) * MOVE_SPEED;
		move_y = sin(game->player.angle) * MOVE_SPEED;
	}
	if (game->key.s_pressed == 1)
	{
		move_x = -cos(game->player.angle) * MOVE_SPEED;
		move_y = -sin(game->player.angle) * MOVE_SPEED;
	}
	move_player(game, move_x, move_y);
}

int	keyhook(int keycode, t_game *game)
{
	if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY
		|| keycode == D_KEY || keycode == LEFT_KEY || keycode == RIGHT_KEY)
	{
		if (keycode == W_KEY)
			game->key.w_pressed = 1;
		if (keycode == A_KEY)
			game->key.a_pressed = 1;
		if (keycode == S_KEY)
			game->key.s_pressed = 1;
		if (keycode == D_KEY)
			game->key.d_pressed = 1;
		if (keycode == LEFT_KEY)
			game->key.left_rotate = 1;
		if (keycode == RIGHT_KEY)
			game->key.right_rotate = 1;
		khook(game, 0, 0);
	}
	if (keycode == ESC)
		x_close_window(game);
	return (0);
}
