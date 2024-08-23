/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousekey_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:48:30 by mlow              #+#    #+#             */
/*   Updated: 2023/12/05 15:48:38 by mlow             ###   ########.fr       */
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

static void	keyhook_movement(int keycode, t_game *game)
{
	int		x;
	int		y;

	x = game->player.pixel_x;
	y = game->player.pixel_y;
	if (keycode == W_KEY)
		move(game, game->player.dir_x, game->player.dir_y);
	if (keycode == S_KEY)
		move(game, -(game->player.dir_x), -(game->player.dir_y));
	if (keycode == A_KEY)
	{
		rotate(&game->player.dir_x, &game->player.dir_y, -ROTATE_SPEED);
		rotate(&game->player.plane_x, &game->player.plane_y, -ROTATE_SPEED);
	}
	if (keycode == D_KEY)
	{
		rotate(&game->player.dir_x, &game->player.dir_y, ROTATE_SPEED);
		rotate(&game->player.plane_x, &game->player.plane_y, ROTATE_SPEED);
	}
	debug_check(game);//@debug.c file but basically it printf all current values.
}

int	keyhook(int keycode, t_game *game)
{
//
	if (keycode == W_KEY || keycode == A_KEY 
		|| keycode == S_KEY || keycode == D_KEY)
	{
		keyhook_movement(keycode, game);
		mixpixel_render(game);
	}
//
	if (keycode == ESC)
		x_close_window(game);
	printf("%d, %c\n", keycode, keycode);
	return (0);
}
