/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:10:17 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 17:01:48 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	open_testmap(t_game *game, char *map_path)
{
	char	*readmap;

	game->data.fd = open(map_path, O_RDONLY);
	if (game->data.fd < 0)
		print_msg("Unable to open map.fd, path not found\n", 1);
	readmap = get_variable_cub(game);
	if (!readmap || !readmap[0])
		free_end_exit("MAP IS EMPTY!!!", 1, game, &readmap);
	if (!check_cub_valid_or_not(game, &readmap))
		free_end_exit("Error\n", 1, game, &readmap);
	if (!get_variable_element(game, &readmap))
		free_end_exit("Error\n", 1, game, &readmap);
	free(readmap);
}
