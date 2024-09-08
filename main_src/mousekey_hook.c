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

int	move2(t_game *game, double dx, double dy)
{
	double	new_pos_x;
	double	new_pos_y;

	printf("dx: %f, dy: %f\n", dx, dy);

	new_pos_x = game->player.pixel_x + dx * MOVE_SPEED;
	new_pos_y = game->player.pixel_y + dy * MOVE_SPEED;
	printf("\n\nnewpos x = %f, y = %f %c\n\n", new_pos_x, new_pos_y, game->data.map2d[(int)(new_pos_y / TILE_SIZE)][(int)(new_pos_x / TILE_SIZE)]);
	// if (new_pos_x < 0 || new_pos_x >= game->data.map_w_in_pixels
	// 	|| new_pos_y < 0 || new_pos_y >= game->data.map_h_in_pixels
	// 	|| game->data.map2d[(int)(new_pos_y / TILE_SIZE)][(int)(new_pos_x / TILE_SIZE)] == '1')
	// {
	// 	return (1);
	// }
	game->player.pixel_x = new_pos_x;
	game->player.pixel_y = new_pos_y;
	game->player.p_x = (int)(new_pos_x / TILE_SIZE);
	game->player.p_y = (int)(new_pos_y / TILE_SIZE);
	return (0);
}

int	rotate2(double *x, double *y, double angle, t_game *game)
{
	double	old_x;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
	game->player.angle += angle;
	return (0);
}

void	rotate_player(t_game *game, int i)	// rotate the player
{
	if (i == 1)
	{
		game->player.angle += ROTATE_SPEED; // rotate right
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	else
	{
		game->player.angle -= ROTATE_SPEED; // rotate left
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
}

void	move_player(t_game *game, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(game->player.pixel_x + move_x); // get the new x position
	new_y = roundf(game->player.pixel_y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (game->data.map2d[map_grid_y][map_grid_x] != '1' && \
	(game->data.map2d[map_grid_y][game->player.pixel_x / TILE_SIZE] != '1' && \
	game->data.map2d[game->player.pixel_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		game->player.pixel_x= new_x; // move the player
		game->player.pixel_y= new_y; // move the player
	}
}

void	khook(t_game *game, double move_x, double move_y)	// hook the player
{
	if (game->key.right_rotate == 1) //rotate right
		rotate_player(game, 1);
	if (game->key.left_rotate == 1) //rotate left
		rotate_player(game, 0);
	if (game->key.d_pressed == 1) //move right
	{
		move_x = -sin(game->player.angle) * MOVE_SPEED;
		move_y = cos(game->player.angle) * MOVE_SPEED;
	}
	if (game->key.a_pressed == 1) //move left
	{
		move_x = sin(game->player.angle) * MOVE_SPEED;
		move_y = -cos(game->player.angle) * MOVE_SPEED;
	}
	if (game->key.w_pressed == 1) //move up
	{
		move_x = cos(game->player.angle) * MOVE_SPEED;
		move_y = sin(game->player.angle) * MOVE_SPEED;
	}
	if (game->key.s_pressed == 1) //move down
	{
		move_x = -cos(game->player.angle) * MOVE_SPEED;
		move_y = -sin(game->player.angle) * MOVE_SPEED;
	}
	move_player(game, move_x, move_y); // move the player
}

void	keyhook_movement2(t_game *game)
{
	printf("presed\n");
	if (game->key.w_pressed)
		move2(game, 0, 1);
	if (game->key.s_pressed)
		move2(game, 0, -1);
	if (game->key.a_pressed)
		move2(game, 1, 0);
	if (game->key.d_pressed)
		move2(game, -1, 0);
	if (game->key.left_rotate)
	{
		rotate2(&game->player.dir_x, &game->player.dir_y, -ROTATE_SPEED, game);
		rotate2(&game->player.plane_x, &game->player.plane_y, -ROTATE_SPEED, game);
	}
	if (game->key.right_rotate)
	{
		rotate2(&game->player.dir_x, &game->player.dir_y, ROTATE_SPEED, game);
		rotate2(&game->player.plane_x, &game->player.plane_y, ROTATE_SPEED, game);
	}
	printf("px: %d, py: %d\n", game->player.pixel_x, game->player.pixel_y);
	//debug_check(game);//@debug.c file but basically it printf all current values.
}

int	keyhook_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
	{
		game->key.w_pressed = 0;
		//printf("KEY W RELEASED = %d!!!\n", game->key.w_pressed);
	}
	if (keycode == A_KEY)
	{
		game->key.a_pressed = 0;
		//printf("KEY A RELEASED = %d!!!\n", game->key.a_pressed);
	}
	if (keycode == S_KEY)
	{
		game->key.s_pressed = 0;
		//printf("KEY S RELEASED = %d!!!\n", game->key.s_pressed);
	}
	if (keycode == D_KEY)
	{
		game->key.d_pressed = 0;
		//printf("KEY D RELEASED = %d!!!\n", game->key.d_pressed);
	}
	if (keycode == LEFT_KEY)
	{
		game->key.left_rotate = 0;
		//printf("KEY D RELEASED = %d!!!\n", game->key.left_rotate);
	}
	if (keycode == RIGHT_KEY)
	{
		game->key.right_rotate = 0;
		//printf("KEY D RELEASED = %d!!!\n", game->key.right_rotate);
	}
	return (0);
}

int	keyhook(int keycode, t_game *game)
{
//
	if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY || keycode == D_KEY
		|| keycode == LEFT_KEY || keycode == RIGHT_KEY)
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
		// mixpixel_render(game);
	}
	if (keycode == ESC)
		x_close_window(game);
	printf("%d, %c\n", keycode, keycode);
	return (0);
}