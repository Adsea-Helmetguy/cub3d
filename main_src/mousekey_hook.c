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

int	keyhook(int keycode, t_game *game)
{
	printf("%d, %c\n", keycode, keycode);
/*
	if (keycode == W_KEY || keycode == A_KEY 
		|| keycode == S_KEY || keycode == D_KEY)
		update_position_player(game, keycode);
	else 
*/
	if (keycode == ESC)
		x_close_window(game);
	return (0);
}
