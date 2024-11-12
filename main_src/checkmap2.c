/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:35:29 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 17:24:42 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	tmp_map2_helper2(char **tmp_map, char ***tmp_map2)
{
	int		array;

	array = -1;
	while (tmp_map[++array])
		(*tmp_map2)[array + 2] = ft_strdup_checkmap(tmp_map[array]);
	(*tmp_map2)[array + 2] = ft_strdup((*tmp_map2)[1]);
	(*tmp_map2)[array + 3] = ft_strdup((*tmp_map2)[0]);
	(*tmp_map2)[array + 4] = NULL;
}

char	**tmp_map2_helper(t_game *game, char **tmp_map)
{
	char	**tmp_map2;
	int		index;

	tmp_map2 = malloc(sizeof(char *) * (game->data.map_h + 5));
	if (!(tmp_map2))
		game_checkerror_exit("malloc @tmp_map2_helper", game);
	tmp_map2[0] = malloc(sizeof(char) * (game->data.map_w + 5));
	tmp_map2[1] = malloc(sizeof(char) * (game->data.map_w + 5));
	if (!(tmp_map2[0]) || !(tmp_map2[1]))
		array_free_exit("malloc @tmp_map2_helper", game, &tmp_map2);
	index = -1;
	while (++index < (game->data.map_w + 4))
		tmp_map2[0][index] = '1';
	tmp_map2[0][index] = '\0';
	tmp_map2[1][0] = '1';
	index = 0;
	while (++index < (game->data.map_w + 3))
		tmp_map2[1][index] = '~';
	tmp_map2[1][index] = '1';
	tmp_map2[1][index + 1] = '\0';
	tmp_map2_helper2(tmp_map, &tmp_map2);
	return (tmp_map2);
}
