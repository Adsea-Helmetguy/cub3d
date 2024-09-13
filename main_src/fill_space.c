/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_image_testmap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:29:06 by mlow              #+#    #+#             */
/*   Updated: 2024/08/11 17:29:19 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//fill the void/null spaces with invalid chars till map_w
char	**fill_space_void(t_game *game, char **map)
{
	char	**tmp_map;
	int	array;
	int	size;
	int	index;

//	printf("value of height: %d\n", game->data.map_h);
//	printf("value of width: %d\n", game->data.map_w);
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

static void 	tab_helper(char ***tmp_map)
{
	int		index;
	int		array;

	array = -1;
//	printf("\n-------------------newtmp_map-------------------------\n\n");
	while ((*tmp_map) && (*tmp_map)[++array])
	{
//		printf("tmp_map[%d]: %s\n", array, (*tmp_map)[array]);
		index = -1;
		while ((*tmp_map)[array] && (*tmp_map)[array][++index])
		{
			if ((*tmp_map)[array][index] == ' ' || (*tmp_map)[array][index] == '~')
				(*tmp_map)[array][index] = '~';
		}
	}
}

//fill all the space/tabs with invalid chars
int	fill_space_tab(t_game *game, char ***tmp_map)
{
	int	array;
	int	index;
	int	gottem;

	tab_helper(tmp_map);
	array = -1;
	gottem = 0;
//	printf("\n-------------------newtmp_map-------------------------\n\n");
	while ((*tmp_map) && (*tmp_map)[++array])
	{
		index = -1;
		while ((*tmp_map)[array][++index])
		{
			if ((*tmp_map)[array][index] == 'N' || (*tmp_map)[array][index] == 'S'
				|| (*tmp_map)[array][index] == 'E' || (*tmp_map)[array][index] == 'W')
			{
				gottem += 1;
				game->player.p_x = index;//width
				game->player.p_y = array;//height
			}
		}
	}
	if (gottem != 1)
		printf("map fails, wrong number of either \"N,S,E,W\"!!! Found(%d).\n", gottem);
	// printf("game->player.p_y: %d\ngame->player.p_x: %d\n", game->player.p_y, game->player.p_x);
	return (gottem);
}
