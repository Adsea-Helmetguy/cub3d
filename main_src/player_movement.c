/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:31:29 by mlow              #+#    #+#             */
/*   Updated: 2024/08/29 19:12:41 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
To rotate a vector, multiply it with the rotation matrix
[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]
watch videos about vectors and matrices
*/
int	rotate(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
	return (0);
}

/*
static void	key_bind(int keycode, void *param)
{
	int key_states[256] = {0};

	key_states[119] = 1; // Mark the key as pressed
	return (0);
}

static void	key_release(int keycode, void *param)
{
	int key_states[256] = {0};

	key_states[119] = 1; // Mark the key as pressed
	return (0);
}
*/

int	move(t_game *game, double dx, double dy)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pixel_x + dx * MOVE_SPEED;
	new_pos_y = game->player.pixel_y + dy * MOVE_SPEED;
	if (new_pos_x < 0 || new_pos_x >= game->data.map_w_in_pixels
		|| new_pos_y < 0 || new_pos_y >= game->data.map_h_in_pixels
		|| game->data.map2d[(int)(new_pos_y / TILE_SIZE)][(int)(new_pos_x / TILE_SIZE)] == '1')
	{
		return (1);
	}
	game->player.pixel_x = new_pos_x;
	game->player.pixel_y = new_pos_y;
	game->data.p_x = (int)(new_pos_x / TILE_SIZE);
	game->data.p_y = (int)(new_pos_y / TILE_SIZE);
	return (0);
}
