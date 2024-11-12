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

static int	valid_char(t_game *game, char **map)
{
	int	index;
	int	array;

	array = -1;
	while (map && map[++array])
	{
		index = 0;
		while (map[array] && map[array][index])
		{
			if (map[array][index] == '0' || map[array][index] == '1'
				|| map[array][index] == 'N' || map[array][index] == 'S'
				|| map[array][index] == 'E' || map[array][index] == 'W'
				|| map[array][index] == ' ' || map[array][index] == '\t')
			{
				index++;
				if (game->data.map_w < index)
					game->data.map_w = index;
			}
			else
				return (0);
		}
	}
	return (1);
}

char	*ft_strdup_checkmap(const char *s)
{
	char		*dest;
	size_t		i;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s) + 5));
	if (dest == NULL)
		return (NULL);
	dest[0] = '1';
	dest[1] = '~';
	i = 0;
	while (s[i] != '\0')
	{
		dest[i + 2] = s[i];
		i++;
	}
	dest[i + 2] = '~';
	dest[i + 3] = '1';
	dest[i + 4] = '\0';
	return (dest);
}

static void	checkmap_validhelper(t_game *game, char **tmp_map)
{
	int	array;

	ftps_free(game->data.map2d);
	game->data.map2d = malloc(sizeof(char *) * (game->data.map_h + 1));
	if (!(game->data.map2d))
		game_checkerror_exit("malloc @checkmapvalidhelper", game);
	array = -1;
	while (++array < game->data.map_h)
		game->data.map2d[array] = ft_strdup(tmp_map[array]);
	game->data.map2d[array] = NULL;
}

int	checkmap_valid(t_game *game, char **data_map2d)
{
	char	**tmp_map;
	char	**tmp_map2;

	if (!valid_char(game, data_map2d))
		return (0);
	tmp_map = fill_space_void(game, data_map2d);
	if (tmp_map && fill_space_tab(game, &tmp_map) != 1)
	{
		ftps_free(tmp_map);
		return (0);
	}
	map_floodfill(&tmp_map, game, game->player.p_x, game->player.p_y);
	map_floodfill2(&tmp_map, game, game->player.p_x, game->player.p_y);
	tmp_map2 = tmp_map2_helper(game, tmp_map);
	game->data.is_map_valid = 1;
	map_floodfill_checker(&tmp_map2, game, 1, 1);
	checkmap_validhelper(game, tmp_map);
	if (tmp_map2)
		ftps_free(tmp_map2);
	if (tmp_map)
		ftps_free(tmp_map);
	return (game->data.is_map_valid);
}
