/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_valid_or_not.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:29:24 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 17:20:38 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//count till i hit the newline and return the strlen
//then i use that value to plusplus to go forward
static	int	count_till_newline(char *findmap)
{
	int	index;

	index = 0;
	while (findmap && findmap[index])
	{
		index++;
		if (findmap[index] == '\n')
		{
			index++;
			break ;
		}
	}
	return (index);
}

static char	*lines_checker(int correct_lines, char *findmap)
{
	char	*map_get;

	map_get = NULL;
	if (correct_lines == 6)
	{
		while (ft_strncmp(findmap, "\n", 1) == 0)
			findmap++;
		map_get = ft_strdup(findmap);
	}
	return (map_get);
}

static	char	*check_beforemap(char *map)
{
	int		index;
	int		correct_lines;
	char	*map_getter;

	map_getter = NULL;
	correct_lines = 0;
	while (correct_lines != 6)
	{
		index = 0;
		if (ft_strncmp(map, "NO ", 3) == 0 || ft_strncmp(map, "SO ", 3) == 0
			|| ft_strncmp(map, "WE ", 3) == 0 || ft_strncmp(map, "EA ", 3) == 0
			|| ft_strncmp(map, "F ", 2) == 0 || ft_strncmp(map, "C ", 2) == 0
			|| ft_strncmp(map, "\n", 1) == 0)
		{
			correct_lines++;
			index = count_till_newline(map);
			map += index;
		}
		else
			break ;
	}
	map_getter = lines_checker(correct_lines, map);
	return (map_getter);
}

static int	check_any_newlines_inbetween(char *map)
{
	int	index;

	index = 0;
	while (map && map[index])
	{
		while (map[index] && map[index] != '\n')
			index++;
		if (map[index] && map[0] != '\n' && map[index] == '\n')
		{
			map += (index + 1);
			index = 0;
		}
		else
			return (0);
	}
	return (1);
}

int	check_cub_valid_or_not(t_game *game, char **readmap)
{
	char	*findmap;
	char	*map_stuff;

	game->data.all_correct_elements = -1;
	findmap = ft_strdup(*readmap);
	map_stuff = check_beforemap(findmap);
	free(findmap);
	if (!map_stuff || map_stuff == NULL)
	{
		free(map_stuff);
		return (0);
	}
	if (map_stuff && !check_any_newlines_inbetween(map_stuff))
	{
		free(map_stuff);
		return (0);
	}
	free(map_stuff);
	return (1);
}
