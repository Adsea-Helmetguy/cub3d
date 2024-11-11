/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:25:37 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 18:36:58 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	mlxpixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
		return ;
	dst = game->mlx.addr + (y * game->mlx.line_length + x
			* (game->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mlxpixel_on_screen(t_game *game)
{
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!game->mlx.img_ptr)
	{
		game->error_code = 1;
		return ;
	}
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr,
			&game->mlx.bits_per_pixel, &game->mlx.line_length,
			&game->mlx.endian);
	if (!game->mlx.addr)
	{
		game->error_code = 1;
		return ;
	}
}
