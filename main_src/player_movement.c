/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:31:29 by mlow              #+#    #+#             */
/*   Updated: 2024/08/20 16:31:34 by mlow             ###   ########.fr       */
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

int	move(t_game *game, double dx, double dy)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pixel_x + dx * MOVE_SPEED;
	new_pos_y = game->player.pixel_y + dy * MOVE_SPEED;
	printf("value of new_pos_x: %f\n", new_pos_x);
	printf("value of new_pos_y: %f\n", new_pos_y);
	printf("value of new_pos_x: %d\n", (int)(new_pos_x / TILE_SIZE));
	printf("value of new_pos_y: %d\n", (int)(new_pos_y / TILE_SIZE));
	printf("value of game->data.map_w: %d\n", game->data.map_w);
	printf("value of game->data.map_h: %d\n", game->data.map_h);
	//printf("value of game->data.map2d[(int)new_pos_y][(int)new_pos_x] %c\n", game->data.map2d[(int)new_pos_y][(int)new_pos_x]);
	if (new_pos_x < 0 || new_pos_x >= game->data.map_w_in_pixels
		|| new_pos_y < 0 || new_pos_y >= game->data.map_h_in_pixels
		|| game->data.map2d[(int)(new_pos_y / TILE_SIZE)][(int)(new_pos_x / TILE_SIZE)] == '1')
	{
		return (1);
	}
	game->player.pixel_x = new_pos_x;
	game->player.pixel_y = new_pos_y;
	printf("value of player.pixel_x: %f\n", game->player.pixel_x);
	printf("value of player.pixel_y: %f\n", game->player.pixel_y);
	return (0);
}
