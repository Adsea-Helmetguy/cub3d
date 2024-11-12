/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:03:45 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 16:58:44 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//	make re && clear && valgrind --leak-check=full --show-leak-kinds=all
//	--track-origins=yes
//	./cub3D assets/cub_maps/invalid_cub/invalid_rgb2.cub
void	free_gameloop_end(char *message, int exit_code, t_game *game)
{
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
	if (game->textures)
		free_textures(game->textures);
	close(game->data.fd);
	print_msg(message, exit_code);
}

void	free_end_exit(char *message, int exit_code, t_game *game, char **str)
{
	if (*str)
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
	close(game->data.fd);
	print_msg(message, exit_code);
}

void	free_before_game(char *message, int exit_code, t_game *game)
{
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
	close(game->data.fd);
	print_msg(message, exit_code);
}
