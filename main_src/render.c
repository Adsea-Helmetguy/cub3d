/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:21:32 by cwijaya           #+#    #+#             */
/*   Updated: 2024/11/12 14:44:44 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// put the pixel
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlxpixel(game, x, y, color);
}

// get the color of the wall
int	get_wall_color(t_game *game, double px, double wall_height, int face)
{
	int		x;
	double	scale;
	double	y;

	y = (px - ((SCREEN_HEIGHT - wall_height) / 2)) / wall_height
		* game->texture_height[face];
	scale = game->texture_width[face] / (double)TILE_SIZE;
	if (game->data.flag == 1)
		x = (int)fmod((game->player.hx * scale), game->texture_width[face]);
	else
		x = (int)fmod((game->player.vy * scale), game->texture_width[face]);
	if (face == SOUTH || face == WEST)
		x *= -1;
	x = ((int)(x) % game->texture_width[face] + game->texture_width[face])
		% game->texture_width[face];
	return (game->textures[face][(int)y * game->texture_width[face] + (int)x]);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// get_color_of_wall
int	px_color(double angle, double px, double wall_height, t_game *game)
{
	angle = nor_angle(angle);
	if (px < (SCREEN_HEIGHT - wall_height) / 2)
		return (create_rgb(game->elements.ceiling_color[0],
				game->elements.ceiling_color[1],
				game->elements.ceiling_color[2]));
	else if (px > (SCREEN_HEIGHT + wall_height) / 2)
		return (create_rgb(game->elements.floor_color[0],
				game->elements.floor_color[1], game->elements.floor_color[2]));
	else
	{
		if (game->data.flag == 0)
		{
			if (angle > M_PI / 2 && angle < 3 * (M_PI / 2))
				return (get_wall_color(game, px, wall_height, WEST));
			else
				return (get_wall_color(game, px, wall_height, EAST));
		}
		else
		{
			if (angle > 0 && angle < M_PI)
				return (get_wall_color(game, px, wall_height, SOUTH));
			else
				return (get_wall_color(game, px, wall_height, NORTH));
		}
	}
}

void	render(t_game *game, int ray, double angle)
{
	double	wall_height;
	double	px;

	game->data.distance *= cos(nor_angle(angle - game->player.angle));
	wall_height = ((SCREEN_WIDTH / 2) / tan(game->data.radfov / 2) * (TILE_SIZE
				/ game->data.distance));
	if (game->data.distance == 0 || wall_height == INFINITY
		|| wall_height == -INFINITY)
		wall_height = SCREEN_HEIGHT;
	px = 0;
	while (px < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, ray, px, px_color(angle, px, wall_height, game));
		px++;
	}
}
