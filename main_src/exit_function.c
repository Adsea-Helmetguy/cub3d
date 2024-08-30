/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:03:45 by mlow              #+#    #+#             */
/*   Updated: 2023/12/06 00:20:26 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
void	end_exit(char *message, int exit_code, t_game *game)
{
	int	array;

	if (exit_code == 2)
	{
		array = -1;
		if (game->map.row)
		{
			while (game->map.row[++array])
				free(game->map.row[array]);
			free(game->map.row);
		}
		array = -1;
		if (game->map.grid)
		{
			while (game->map.grid[++array])
				free(game->map.grid[array]);
			free(game->map.grid);
		}
		exit_code = 1;
	}
	close(game->map.fd);
	print_message(message, exit_code);
}
*/
void	end_exit(char *message, int exit_code, t_game *game)
{
	(void)game;
	//close(game->data.fd);
	print_msg(message, exit_code);
}

void	free_end_exit(char *message, int exit_code, t_game *game, char **str)
{
	if (str && *str)
	{
		free(*str);
		str = NULL;
	}
	if (game->elements.north_texture)
		free(game->elements.north_texture);
	if (game->elements.south_texture)
		free(game->elements.south_texture);
	if (game->elements.west_texture)
		free(game->elements.west_texture);
	if (game->elements.east_texture)
		free(game->elements.east_texture);
	if (game->data.map2d)
		ftps_free(game->data.map2d);
	end_exit(message, exit_code, game);
}
