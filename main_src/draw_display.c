/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:36:24 by mlow              #+#    #+#             */
/*   Updated: 2024/09/03 16:25:07 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	draw_background(t_game *game)
{
	int	width;
	int	height;

/*
//doesnt refresh everything
	while (++height < (game->data.map_h * TILE_SIZE))
	{
		width = -1;
		while (++width < (game->data.map_w * TILE_SIZE))
			mlxpixel(game, width, height, 0x00000000);
	}
*/
	height = -1;
	while (++height < (SCREEN_HEIGHT))
	{
		width = -1;
		while (++width < (SCREEN_WIDTH))
			mlxpixel(game, width, height, 0x00000000);
	}
}


static int	drawlines_width(int width, int index, int array, t_game *game)
{
	int	height;

	while (width <= ((index + 1) * TILE_SIZE))
	{
		height = (array * TILE_SIZE);
		while (height < (array + 1) * TILE_SIZE)
		{
			if (game->data.map2d[array][index] == '1')
				mlxpixel(game, width, height, 0x00ffffff);
			height++;
		}
		if (game->data.map2d[array][index] == '1'
			|| game->data.map2d[array][index] == '0'
			|| game->data.map2d[array][index] == ' ')
		{
			mlxpixel(game, width, (array * TILE_SIZE), 0x000000ff);
			mlxpixel(game, width, ((array + 1) * TILE_SIZE), 0x000000ff);
		}
		width++;
	}
	return (width);
}

static void	drawlines_height(int index, int array, t_game *game)
{
	int	height;

	height = (array * TILE_SIZE);
	while (height <= ((array + 1) * TILE_SIZE))
	{
		if (game->data.map2d[array][index] == '1'
			|| game->data.map2d[array][index] == '0'
			|| game->data.map2d[array][index] == ' ')
		{
			mlxpixel(game, (index * TILE_SIZE), height, 0x000000ff);
			mlxpixel(game, ((index + 1) * TILE_SIZE), height, 0x000000ff);
		}
		height++;
	}
	index++;
}

static void	draw_boxes(t_game *game)
{
	int	array;
	int	index;
	int	width;

	if (game->data.map2d)
	{
		array = 0;
		while (game->data.map2d[array])
		{
			width = 0;
			index = 0;
			while (game->data.map2d[array][index])
			{
				width = drawlines_width(width, index, array, game);
				drawlines_height(index, array, game);
				index++;
			}
			array++;
		}
	}
}

static void	draw_player(t_game *game)
{
	int	width;
	int	height;

	//thanks to init_variable_player, we have player width and height
	mlxpixel(game, game->player.pixel_x, game->player.pixel_y, 0x00FFFF00);
	height = (game->player.pixel_y - (TILE_SIZE / 10));
	while (height <= game->player.pixel_y + (TILE_SIZE / 10))
	{
		width = (game->player.pixel_x - (TILE_SIZE / 10));
		while (width <= game->player.pixel_x + (TILE_SIZE / 10))
		{
			mlxpixel(game, width, height, 0x00FFFF00);
			width++;
		}
		height++;
	}
}


static void	draw_ray(t_game *game)
{
//	int	x_end;
//	int	y_end;
	int	x_start;
	int	y_start;

//	x_end = game->player.p_x + game->ray.dir_x;
//	y_end = game->player.p_y + game->ray.dir_y;
	x_start = game->player.pixel_x;
	y_start = game->player.pixel_y;

	//this works and avoids all the walls
	while (y_start > 0 && game->data.map2d[y_start / TILE_SIZE][x_start / TILE_SIZE] != '1')
		mlxpixel(game, x_start, --y_start, 0x00FF0000);
	y_start = game->player.pixel_y;
	while (x_start > 0 && game->data.map2d[y_start / TILE_SIZE][x_start / TILE_SIZE] != '1')
		mlxpixel(game, --x_start, y_start, 0x00FF0000);
	x_start = game->player.pixel_x;
	while (x_start < SCREEN_WIDTH
		&& game->data.map2d[y_start / TILE_SIZE][x_start / TILE_SIZE] != '1')
		mlxpixel(game, ++x_start, y_start, 0x00FF0000);
	x_start = game->player.pixel_x;
	while (y_start < SCREEN_HEIGHT 
		&& game->data.map2d[y_start / TILE_SIZE][x_start / TILE_SIZE] != '1')
		mlxpixel(game, x_start, ++y_start, 0x00FF0000);
//
/*
	//this works by showing the current blank
	while (y_start > (game->player.p_y) * TILE_SIZE)
		mlxpixel(game, x_start, --y_start, 0x00FF0000);
	y_start = game->player.pixel_y;
	while (x_start > (game->player.p_x) * TILE_SIZE)
		mlxpixel(game, --x_start, y_start, 0x00FF0000);
	x_start = game->player.pixel_x;
	while (x_start < (game->player.p_x + 1) * TILE_SIZE)
		mlxpixel(game, ++x_start, y_start, 0x00FF0000);
	x_start = game->player.pixel_x;
	while (y_start < (game->player.p_y + 1) * TILE_SIZE)
		mlxpixel(game, x_start, ++y_start, 0x00FF0000);
*/

}


void	draw_display(t_game *game)
{
	//draw_background(game);
	draw_boxes(game);
	draw_player(game);
	draw_ray(game);
	//add others
}
