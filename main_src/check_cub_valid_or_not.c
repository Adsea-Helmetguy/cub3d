/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:29:24 by mlow              #+#    #+#             */
/*   Updated: 2024/08/03 15:57:44 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	//count till i hit the newline and return the strlen 
	//then i use that value to plusplus to go forward
	return (index);
}

static	char	*check_beforemap(char *findmap)
{
	int	index;
	int	correct_lines;
	char	*map_get;

	map_get = NULL;
	correct_lines = 0;
	while (correct_lines != 6)
	{
		index = 0;
		if (ft_strncmp(findmap, "NO ", 3) == 0 || ft_strncmp(findmap, "SO ", 3) == 0
			|| ft_strncmp(findmap, "WE ", 3) == 0 || ft_strncmp(findmap, "EA ", 3) == 0
			|| ft_strncmp(findmap, "F ", 2) == 0 || ft_strncmp(findmap, "C ", 2) == 0
			|| ft_strncmp(findmap, "\n", 1) == 0)
		{
			correct_lines++;
			index = count_till_newline(findmap);
			//printf("new index = %d\n", index);
			findmap += index;
		}
		else
		{
			printf("INVALID VALUE!!!Error\n");
			break ;
		}
	}
	//printf("Correct lines = %d\n", correct_lines);
	if (correct_lines == 6)
	{
		while (ft_strncmp(findmap, "\n", 1) == 0)//might need to edit this
			findmap++;//incase if the above uses break and correct lines arent 6
		//printf("findmap[0] = %c\n", findmap[0]);
		map_get = ft_strdup(findmap);
	}
	return (map_get);
}

static int	check_any_newlines_inbetween(char *map)
{
	int 	index;

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
	//printf("\n---------no newlines inbetween maps, GOOD!--------\n");
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
	//printf("\n\n\nstartmap\n----------\n%s\n----------\n", map_stuff);
	if (map_stuff && !check_any_newlines_inbetween(map_stuff))
	{
		free(map_stuff);
		return (0);
	}
	free(map_stuff);
	return (1);
}
