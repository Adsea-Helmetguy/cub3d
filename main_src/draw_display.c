/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:36:24 by mlow              #+#    #+#             */
/*   Updated: 2024/08/12 15:53:18 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	draw_background(t_game *game)
{
	int	width;
	int	height;

	height = -1;
	while (++height < (game->data.map_h * TILE_SIZE))
	{
		width = -1;
		while (++width < (game->data.map_w * TILE_SIZE))
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
	mlxpixel(game, game->player.width, game->player.height, 0x00FFFF00);
	height = (game->player.height - (TILE_SIZE / 10));
	while (height <= game->player.height + (TILE_SIZE / 10))
	{
		width = (game->player.width - (TILE_SIZE / 10));
		while (width <= game->player.width + (TILE_SIZE / 10))
		{
			mlxpixel(game, width, height, 0x00FFFF00);
			width++;
		}
		height++;
	}
	
}

void	draw_display(t_game *game)
{
	draw_background(game);
	draw_boxes(game);
	draw_player(game);
	//add others
}
/*
------------------
|Original working|
------------------
static void	draw_boxes(t_game *game)
{
	int	index;
	int	array;
	int	width;
	int	height;

	if (game->data.map2d)
	{
		array = 0;
		while (game->data.map2d[array])
		{
			width = 0;
			index = 0;
			while (game->data.map2d[array][index])
			{
				while (width <= ((index + 1) * TILE_SIZE))
				{
					height = (array * TILE_SIZE);
					while (height < (array + 1) * TILE_SIZE)
					{
						if (game->data.map2d[array][index] == '1')
							mlxpixel(game, width, height, 0x00ffffff);
						height++;
					}
					if (game->data.map2d[array][index] == '1')
					{
						mlxpixel(game, width, (array * TILE_SIZE), 0x000000ff);
						mlxpixel(game, width, ((array + 1) * TILE_SIZE), 0x000000ff);
					}
					width++;
				}
				height = (array * TILE_SIZE);
				while (height <= ((array + 1) * TILE_SIZE))
				{
					if (game->data.map2d[array][index] == '1')
					{
						mlxpixel(game, (index * TILE_SIZE), height, 0x000000ff);
						mlxpixel(game, ((index + 1) * TILE_SIZE), height, 0x000000ff);
					}
					height++;
				}
				index++;
			}
			array++;
		}
	}
}
*/
