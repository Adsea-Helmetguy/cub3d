/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:04:55 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 18:47:32 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*get_variable_cub(t_game *game)
{
	char	*readmap;
	char	*tmp;
	char	*newline;

	readmap = (char *)malloc(sizeof(char) * 1);
	if (!readmap)
		return (NULL);
	readmap[0] = '\0';
	while (1)
	{
		newline = get_next_line(game->data.fd);
		if (!newline)
			break ;
		if (newline)
		{
			tmp = readmap;
			readmap = ft_strjoin(tmp, newline);
			free(tmp);
			free(newline);
		}
	}
	return (readmap);
}

void	get_variable_map(t_game *game, char **split_map)
{
	int		array;
	int		row;

	array = 5;
	row = 0;
	while (split_map && split_map[++array])
		row++;
	game->data.map2d = malloc(sizeof(char *) * (row + 1));
	if (!(game->data.map2d))
		game_checkerror_exit("malloc @checkmapvalidhelper", game);
	array = 5;
	row = -1;
	while (split_map && split_map[++array])
		game->data.map2d[++row] = ft_strdup(split_map[array]);
	game->data.map2d[++row] = NULL;
	game->data.map_h = row;
}

static int	checkcolor_value(char **split_map, int value_return, t_game *game)
{
	if (getting_color(split_map, "F", game->elements.floor_color) != 0)
	{
		printf("There was an error in getting \"F\" Floor_color\n");
		ftps_free(split_map);
		printf("value_return: %d\n", value_return);
		return (0);
	}
	if (getting_color(split_map, "C", game->elements.ceiling_color) != 0)
	{
		printf("There was an error in getting \"C\" Celling_color\n");
		ftps_free(split_map);
		printf("value_return: %d\n", value_return);
		return (0);
	}
	printf("color: %d\n", game->elements.floor_color[0]);
	printf("color: %d\n", game->elements.floor_color[1]);
	printf("color: %d\n", game->elements.floor_color[2]);
	return (1);
}

static int	check_textures(char **split_map, t_game *game)
{
	if (!(game->elements.north_texture) || !(game->elements.south_texture)
		|| !(game->elements.west_texture) || !(game->elements.east_texture))
	{
		printf("There was an error in either NO/SO/WE or EA\n");
		ftps_free(split_map);
		return (0);
	}
	return (1);
}

int	get_variable_element(t_game *game, char **readmap)
{
	char	**split_map;
	int		value_return;

	value_return = 1;
	split_map = ft_split(*readmap, '\n');
	game->elements.north_texture = search_for_value(split_map, "NO");
	printf("\n\nNORTH_texture value: %s\n", game->elements.north_texture);
	game->elements.south_texture = search_for_value(split_map, "SO");
	printf("SOUTH_texture: %s\n", game->elements.south_texture);
	game->elements.west_texture = search_for_value(split_map, "WE");
	printf("WEST_texture: %s\n", game->elements.west_texture);
	game->elements.east_texture = search_for_value(split_map, "EA");
	printf("EAST_texture: %s\n", game->elements.east_texture);
	if (check_textures(split_map, game) == 0
		|| checkcolor_value(split_map, value_return, game) == 0)
		return (0);
	get_variable_map(game, split_map);
	if (!checkmap_valid(game, game->data.map2d))
		value_return = 0;
	ftps_free(split_map);
	return (value_return);
}
