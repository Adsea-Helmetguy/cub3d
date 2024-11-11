/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:29:06 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 17:45:08 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//fill the void/null spaces with invalid chars till map_w
char	**fill_space_void(t_game *game, char **map)
{
	char	**tmp_map;
	int		array;
	int		size;
	int		index;

	tmp_map = malloc(sizeof(char *) * (game->data.map_h + 1));
	array = -1;
	while (map && map[++array])
	{
		size = ft_strlen(map[array]);
		if (size == game->data.map_w)
			tmp_map[array] = ft_strdup(map[array]);
		else if (size != game->data.map_w)
		{
			tmp_map[array] = malloc(sizeof(char) * (game->data.map_w + 1));
			index = -1;
			while (map[array][++index] != '\0')
				tmp_map[array][index] = map[array][index];
			while (tmp_map[array] && (index < game->data.map_w))
				tmp_map[array][index++] = '~';
			tmp_map[array][index] = '\0';
		}
	}
	tmp_map[array] = NULL;
	return (tmp_map);
}

static void	tab_helper(char ***tmp_map)
{
	int		index;
	int		array;

	array = -1;
	while ((*tmp_map) && (*tmp_map)[++array])
	{
		index = -1;
		while ((*tmp_map)[array] && (*tmp_map)[array][++index])
		{
			if ((*tmp_map)[array][index] == ' '
				|| (*tmp_map)[array][index] == '~')
				(*tmp_map)[array][index] = '~';
		}
	}
}

static int	total_gottem(int array, int gottem, char ***tmp_map, t_game *game)
{
	int	i;

	while ((*tmp_map) && (*tmp_map)[++array])
	{
		i = -1;
		while ((*tmp_map)[array][++i])
		{
			if ((*tmp_map)[array][i] == 'N' || (*tmp_map)[array][i] == 'S'
				|| (*tmp_map)[array][i] == 'E' || (*tmp_map)[array][i] == 'W')
			{
				gottem += 1;
				game->player.p_x = i;
				game->player.p_y = array;
				if ((*tmp_map)[array][i] == 'N')
					game->player.angle = 270 * M_PI / 180;
				else if ((*tmp_map)[array][i] == 'S')
					game->player.angle = 90 * M_PI / 180;
				else if ((*tmp_map)[array][i] == 'E')
					game->player.angle = 0 * M_PI / 180;
				else if ((*tmp_map)[array][i] == 'W')
					game->player.angle = 180 * M_PI / 180;
			}
		}
	}
	return (gottem);
}

//fill all the space/tabs with invalid chars
int	fill_space_tab(t_game *game, char ***tmp_map)
{
	int	array;
	int	index;
	int	gottem;

	tab_helper(tmp_map);
	array = -1;
	gottem = total_gottem(array, 0, tmp_map, game);
	if (gottem != 1)
		printf("Wrong number of \"N,S,E,W\"!!! Found(%d).\n", gottem);
	return (gottem);
}
