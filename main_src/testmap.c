/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:10:17 by mlow              #+#    #+#             */
/*   Updated: 2023/12/06 01:21:16 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	open_testmap(t_game *game, char *map_path)
{
	char	*readmap;

	game->data.fd = open(map_path, O_RDONLY);
	if (game->data.fd < 0)
		end_exit("Unable to open map.fd, path not found", 1, game);
	readmap = get_variable_cub(game);
	if (!readmap || !readmap[0])
		free_end_exit("MAP IS EMPTY!!!", 1, game, &readmap);
	if (!check_cub_valid_or_not(game, &readmap))
		free_end_exit("Error\n", 1, game, &readmap);
	if (!get_variable_element(game, &readmap))
		free_end_exit("Error\n", 1, game, &readmap);
	printf("\n\nVariable values:\n=========================================\n");
	// printf("player_width(x): %d\nplayer_height(y): %d\nmap_width: %d\nmap_height: %d\n"
		// , game->data.p_x, game->data.p_y, game->data.map_w, game->data.map_h);
	printf("==========NOW for player details=========\n");
	free(readmap);
	//close(game->data.fd);
}
