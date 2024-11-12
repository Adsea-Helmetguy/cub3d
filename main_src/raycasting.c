/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:02:59 by cwijaya           #+#    #+#             */
/*   Updated: 2024/11/12 15:24:25 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int	has_wall_at(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= game->data.map_w * TILE_SIZE || y < 0
		|| y >= game->data.map_h * TILE_SIZE)
		return (1);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_x >= game->data.map_w
		|| map_y >= game->data.map_h)
		return (1);
	if (game->data.map2d[map_y][map_x] == '1')
		return (1);
	return (0);
}

double	v_collision(t_game *game, double angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	int		adjust;

	x_intercept = game->player.pixel_x - (game->player.pixel_x % TILE_SIZE);
	adjust = init_v(angle, &x_step, &y_step, &x_intercept);
	y_intercept = game->player.pixel_y + (x_intercept - game->player.pixel_x)
		* tan(angle);
	if (angle == 0 || angle == M_PI)
		return (SCREEN_HEIGHT);
	while (!has_wall_at(game, x_intercept + adjust, y_intercept))
	{
		x_intercept += x_step;
		y_intercept += y_step;
	}
	game->player.vx = x_intercept;
	game->player.vy = y_intercept;
	return (distance(game->player.pixel_x, game->player.pixel_y, x_intercept,
			y_intercept));
}

double	h_collision(t_game *game, double angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	int		adjust;

	y_intercept = game->player.pixel_y - (game->player.pixel_y % TILE_SIZE);
	adjust = init_h(angle, &x_step, &y_step, &y_intercept);
	x_intercept = game->player.pixel_x + ((y_intercept - game->player.pixel_y)
			/ tan(angle));
	if (angle == M_PI / 2 || angle == 3 * (M_PI / 2))
		return (SCREEN_WIDTH);
	while (!has_wall_at(game, x_intercept, y_intercept + adjust))
	{
		x_intercept += x_step;
		y_intercept += y_step;
	}
	game->player.hx = x_intercept;
	game->player.hy = y_intercept;
	return (distance(game->player.pixel_x, game->player.pixel_y, x_intercept,
			y_intercept));
}

void	raycasting(t_game *game)
{
	double	h_col;
	double	v_col;
	double	angle;
	double	increment;
	int		ray;

	ray = 0;
	angle = nor_angle(game->player.angle - (game->data.radfov / 2));
	increment = (double)game->data.radfov / (double)SCREEN_WIDTH;
	while (ray < SCREEN_WIDTH)
	{
		game->data.flag = 0;
		h_col = h_collision(game, angle);
		v_col = v_collision(game, angle);
		if (h_col < v_col)
		{
			game->data.distance = h_col;
			game->data.flag = 1;
		}
		else
			game->data.distance = v_col;
		render(game, ray, angle);
		ray++;
		angle = nor_angle(angle + increment);
	}
}
