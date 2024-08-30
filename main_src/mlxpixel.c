/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:25:37 by mlow              #+#    #+#             */
/*   Updated: 2024/08/12 14:18:54 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int	mixpixel_render(t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)game->player.pixel_x;
	map_y = (int)game->player.pixel_y;
	draw_background(game);
	raycasting_calculation(game, map_x, map_y);
	draw_display(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img_ptr, 0, 0);
	return (0);
}


void	mlxpixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->mlx.addr + (y * game->mlx.line_length + x * (game->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//int offset = (y * line_length + mx * (bits_per_pixel / 8)); //use this in future
void	mlxpixel_on_screen(t_game *game)
{
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, SCREEN_HEIGHT, SCREEN_WIDTH);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bits_per_pixel,
				&game->mlx.line_length, &game->mlx.endian);
	draw_display(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img_ptr, 0, 0);
}
