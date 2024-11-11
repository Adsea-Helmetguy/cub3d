/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:47:40 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 17:45:30 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	map_floodfill(char ***tmp_map, t_game *game, int p_x, int p_y)
{
	if ((p_y - 1) < 0 || (p_x - 1) < 0 || (p_y + 1) >= (game->data.map_h)
		|| (p_x + 1) >= (game->data.map_w) || (*tmp_map)[p_y][p_x] == '1'
		|| (*tmp_map)[p_y][p_x] == 'C')
		return ;
	if ((*tmp_map)[p_y][p_x] != 'N' && (*tmp_map)[p_y][p_x] != 'S'
		&& (*tmp_map)[p_y][p_x] != 'E' && (*tmp_map)[p_y][p_x] != 'W')
		(*tmp_map)[p_y][p_x] = 'C';
	map_floodfill(tmp_map, game, p_x, (p_y - 1));
	map_floodfill(tmp_map, game, p_x, (p_y + 1));
	map_floodfill(tmp_map, game, (p_x - 1), p_y);
	map_floodfill(tmp_map, game, (p_x + 1), p_y);
}

void	map_floodfill2(char ***tmp_map, t_game *game, int p_x, int p_y)
{
	if ((p_y - 1) < 0 || (p_x - 1) < 0 || (p_y + 1) >= (game->data.map_h)
		|| (p_x + 1) >= (game->data.map_w) || (*tmp_map)[p_y][p_x] == '1'
		|| (*tmp_map)[p_y][p_x] == '0')
		return ;
	if ((*tmp_map)[p_y][p_x] != 'N' && (*tmp_map)[p_y][p_x] != 'S'
		&& (*tmp_map)[p_y][p_x] != 'E' && (*tmp_map)[p_y][p_x] != 'W')
		(*tmp_map)[p_y][p_x] = '0';
	map_floodfill2(tmp_map, game, p_x, (p_y - 1));
	map_floodfill2(tmp_map, game, p_x, (p_y + 1));
	map_floodfill2(tmp_map, game, (p_x - 1), p_y);
	map_floodfill2(tmp_map, game, (p_x + 1), p_y);
}

void	map_floodfill_checker(char ***tmp_map, t_game *game, int p_x, int p_y)
{
	if ((p_y - 1) < 0 || (p_x - 1) < 0 || (p_y + 1) >= (game->data.map_h + 4)
		|| (p_x + 1) >= (game->data.map_w + 4) || (*tmp_map)[p_y][p_x] == '1'
		|| (*tmp_map)[p_y][p_x] == '`')
		return ;
	if ((*tmp_map)[p_y][p_x] == 'N' || (*tmp_map)[p_y][p_x] == 'E'
		|| (*tmp_map)[p_y][p_x] == 'S' || (*tmp_map)[p_y][p_x] == 'W')
		game->data.is_map_valid = 0;
	if ((*tmp_map)[p_y][p_x] != 'N' && (*tmp_map)[p_y][p_x] != 'E'
		&& (*tmp_map)[p_y][p_x] != 'W' && (*tmp_map)[p_y][p_x] != 'S')
		(*tmp_map)[p_y][p_x] = '`';
	map_floodfill_checker(tmp_map, game, p_x, (p_y - 1));
	map_floodfill_checker(tmp_map, game, p_x, (p_y + 1));
	map_floodfill_checker(tmp_map, game, (p_x - 1), p_y);
	map_floodfill_checker(tmp_map, game, (p_x + 1), p_y);
}
