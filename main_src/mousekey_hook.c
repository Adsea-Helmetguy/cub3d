/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousekey_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:48:30 by mlow              #+#    #+#             */
/*   Updated: 2024/08/28 20:53:01 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	closehook(t_game *game)
{
	if (game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
		mlx_destroy_display(game->mlx.mlx_ptr);
//	free_data(game);
//	free(game.mlx.win_ptr);
	exit(0);
}

void	keyhook_movement(t_game *game)
{
	int		x;
	int		y;

	x = game->player.pixel_x;
	y = game->player.pixel_y;
	if (game->key.w_pressed)
		move(game, game->player.dir_x, game->player.dir_y);
	if (game->key.s_pressed)
		move(game, -(game->player.dir_x), -(game->player.dir_y));
	if (game->key.a_pressed)
	{
		rotate(&game->player.dir_x, &game->player.dir_y, -ROTATE_SPEED);
		rotate(&game->player.plane_x, &game->player.plane_y, -ROTATE_SPEED);
	}
	if (game->key.d_pressed)
	{
		rotate(&game->player.dir_x, &game->player.dir_y, ROTATE_SPEED);
		rotate(&game->player.plane_x, &game->player.plane_y, ROTATE_SPEED);
	}
	debug_check(game);//@debug.c file but basically it printf all current values.
}

int	keyhook_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
	{
		game->key.w_pressed = 0;
		printf("KEY W RELEASED = %d!!!\n", game->key.w_pressed);
	}
	if (keycode == A_KEY)
	{
		game->key.a_pressed = 0;
		printf("KEY A RELEASED = %d!!!\n", game->key.a_pressed);
	}
	if (keycode == S_KEY)
	{
		game->key.s_pressed = 0;
		printf("KEY S RELEASED = %d!!!\n", game->key.s_pressed);
	}
	if (keycode == D_KEY)
	{
		game->key.d_pressed = 0;
		printf("KEY D RELEASED = %d!!!\n", game->key.d_pressed);
	}
	return (0);
}

int	keyhook(int keycode, t_game *game)
{
//
	if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY || keycode == D_KEY)
	{
		if (keycode == W_KEY)
		{
			game->key.w_pressed = 1;
			printf("game->key.w_pressed = %d!!!\n", game->key.w_pressed);
		}
		if (keycode == A_KEY)
		{
			game->key.a_pressed = 1;
			printf("game->key.a_pressed = %d!!!\n", game->key.a_pressed);
		}
		if (keycode == S_KEY)
		{
			game->key.s_pressed = 1;
			printf("game->key.s_pressed = %d!!!\n", game->key.s_pressed);
		}
		if (keycode == D_KEY)
		{
			game->key.d_pressed = 1;
			printf("game->key.d_pressed = %d!!!\n", game->key.d_pressed);
		}
		keyhook_movement(game);
		//mixpixel_render(game);
	}
//
	if (keycode == ESC)
		x_close_window(game);
	printf("%d, %c\n", keycode, keycode);
	return (0);
}
