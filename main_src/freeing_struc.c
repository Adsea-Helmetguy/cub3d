/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_struc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:07:31 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 17:46:38 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ftps_free(char **to_free)
{
	int	array;

	array = 0;
	if (!to_free)
		return ;
	while (to_free[array])
	{
		free(to_free[array]);
		to_free[array] = NULL;
		array++;
	}
	free(to_free);
	to_free = NULL;
}

void	free_textures(int **game_textures)
{
	int	index;

	index = 0;
	if (!game_textures)
		return ;
	while (index < 4)
	{
		if (game_textures[index])
			free(game_textures[index]);
		index++;
	}
	if (game_textures)
		free(game_textures);
}
