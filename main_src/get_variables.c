/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:04:55 by mlow              #+#    #+#             */
/*   Updated: 2024/07/30 18:06:03 by mlow             ###   ########.fr       */
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
	//printf("\n\n---Readmap---\n%s\n---readmap end---\n\n\n", readmap);
	return (readmap);
}

void	get_variable_map(t_game *game, char **split_map)
{
	int		array;
	int		row;

	array = 5;//array == 5 cause in while loop array starts at "6"
	row = 0;
	while (split_map && split_map[++array])
		row++;
	game->data.map2d = malloc(sizeof(char *) * (row + 1));
//	printf("\n----------map!---------------\n");
//	printf("Inside the split_map while loop!\n");
	array = 5;
	row = -1;
	while(split_map && split_map[++array])
	{
		game->data.map2d[++row] = strdup(split_map[array]);
//		printf("game->data.map2d[%d]->%s\n", row, game->data.map2d[row]);
	}
	game->data.map2d[++row] = NULL;
	game->data.map_h = row;
//	printf("game->data.map2d[%d]->(null)\n", row);
}

int	get_variable_element(t_game *game, char **readmap)
{
	char	**split_map;
	int	value_return;

	value_return = 1;
	split_map = ft_split(*readmap, '\n');
	game->elements.north_texture = search_for_value(split_map, "NO");
//	printf("game->elements.north_texture value: %s\n", game->elements.north_texture);
//	printf("-----------------------------\n\n");
	game->elements.south_texture = search_for_value(split_map, "SO");
//	printf("game->elements.south_texture: %s\n", game->elements.south_texture);
//	printf("-----------------------------\n\n");
	game->elements.west_texture = search_for_value(split_map, "WE");
//	printf("game->elements.west_texture: %s\n", game->elements.west_texture);
//	printf("-----------------------------\n\n");
	game->elements.east_texture = search_for_value(split_map, "EA");
//	printf("game->elements.game->elements.east_texture: %s\n", game->elements.east_texture);
//	printf("-----------------------------\n\n");
	if (!(game->elements.north_texture) || !(game->elements.south_texture)
		|| !(game->elements.west_texture) || !(game->elements.east_texture))
	{
//		printf("There was an error in either NO/SO/WE or EA\n");
		ftps_free(split_map);
		return (0);
	}
	getting_color(split_map, "F", game->elements.floor_color);
//	printf("-----------------------------\n\n");
	getting_color(split_map, "C", game->elements.ceiling_color);
//	printf("-----------------------------\n\n");
//make a if condition for this in case it doesnt get the correct colors!
//mod(256) if the number is bigger 
//	if (!game->elements.floor_color
//	if (!game->elements.ceiling_color
	get_variable_map(game, split_map);
	if (!checkmap_valid(game, game->data.map2d))
		value_return = 0;
	ftps_free(split_map);
	return (value_return);
}
