/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:35:29 by mlow              #+#    #+#             */
/*   Updated: 2024/08/06 18:04:22 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	valid_char(t_game *game, char **map)
{
	int	index;
	int	array;

	array = -1;
	//printf("\n\n\n\n\n\ncheckmap_valid\n---------------------------\n");
	while (map && map[++array])
	{
		index = 0;
		//printf("%s\n", map[array]);
		while (map[array] && map[array][index])
		{
			if (map[array][index] == '0' || map[array][index] == '1' || map[array][index] == 'N'
				|| map[array][index] == 'S' || map[array][index] == 'E' || map[array][index] == 'W'
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

static char	*ft_strdup_checkmap(const char *s)
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

static char 	**tmp_map2_helper(t_game *game, char **tmp_map)
{
	char	**tmp_map2;
	int	array;
	int	index;

	tmp_map2 = malloc(sizeof(char *) * (game->data.map_h + 5));
	tmp_map2[0] = malloc(sizeof(char) * (game->data.map_w + 5));
	tmp_map2[1] = malloc(sizeof(char) * (game->data.map_w + 5));
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
	array = -1;
	while (tmp_map[++array])
		tmp_map2[array + 2] = ft_strdup_checkmap(tmp_map[array]);
	tmp_map2[array + 2] = ft_strdup(tmp_map2[1]);
	tmp_map2[array + 3] = ft_strdup(tmp_map2[0]);
	tmp_map2[array + 4] = NULL;
	return (tmp_map2);
}

static checkmap_validhelper(t_game *game, char **tmp_map)
{
	int	array;

	ftps_free(game->data.map2d);
	game->data.map2d = malloc(sizeof(char *) * (game->data.map_h + 1));
	array = -1;
	while (++array < game->data.map_h)
	{
		game->data.map2d[array] = ft_strdup(tmp_map[array]);
		printf("%s: game->data.new2d[%d]\n", game->data.map2d[array], array);
	}
	game->data.map2d[array] = NULL;
	printf("map_h value = %d\n", game->data.map_h);
	printf("total array for the new map!!!: %d\n", array);
}

//make re && ./cub3D assets/cub_maps/invalid_cub/invalid7.cub
int	checkmap_valid(t_game *game, char **data_map2d)
{
	char	**tmp_map;
	char	**tmp_map2;
	int	array;

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
	tmp_map2 = tmp_map2_helper(game, tmp_map);//box drawn around map!
	game->data.is_map_valid = 1;
	map_floodfill_checker(&tmp_map2, game, 1, 1);
	if (game->data.is_map_valid == 0)
		printf("map is invalid, game->data.is_map_valid == 0\n");
	else
		printf("map is valid, ALL GUD!!!\n");
	//printf("\n-------------------newtmp_map-------------------------\n\n");
//
//
//
//
	checkmap_validhelper(game, tmp_map);
//
//
//
//
	if (tmp_map2)
		ftps_free(tmp_map2);//once we are done with the tmp_map2
	if (tmp_map)
		ftps_free(tmp_map);//once we are done with the tmp_map
	return (game->data.is_map_valid);
}




















