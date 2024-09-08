/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_value_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:39:08 by mlow              #+#    #+#             */
/*   Updated: 2024/08/01 16:39:17 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static char	*search_for_color(char **split_map, char *var_name)
{
	int	array;
	char	**get_color;
	char	*element_color;

	get_color = NULL;
	element_color = NULL;
	array = -1;
//	printf("\n----------%s------------------\n", var_name);
	while(split_map && split_map[++array] && array < 6)
	{
		if (get_color)
			ftps_free(get_color);
		get_color = ft_split(split_map[array], ' ');
		if (!get_color[2] && ft_strcmp(get_color[0], var_name) == 0
			&& ft_isdigit(get_color[1][0]))
		{
			element_color = ft_strdup(get_color[1]);
			break ;
		}
	}
	ftps_free(get_color);
	return (element_color);
}

void	getting_color(char **map, char *var_name, int color[3])
{
	char	*element_color;
	char	**game_color;
	int	array;
	int	index;
	int	all_digits;

	game_color = NULL;
	element_color = search_for_color(map, var_name);
//	printf("value of element_color: %s\n", element_color);
	if (element_color)
	{
		game_color = ft_split(element_color, ',');
		free(element_color);
	}
//check if they are all numbers/digits
	array = -1;
	all_digits = 1;
	while(game_color && game_color[++array])
	{
		index = -1;
		while (game_color[array][++index])
		{
			if (ft_isdigit(game_color[array][index] == 0))
			{
				all_digits = 0;
				break ;
			}
		}
		if (!all_digits)
			break ;
	}
	if (game_color && all_digits)
	{
		array = -1;
		index = -1;
		while (game_color && game_color[++array])
			color[++index] = ft_atoi(game_color[array]);
		ftps_free(game_color);
//can detele
//		index = -1;
//		while (color && ++index < 3)
//		{
//			printf("while loop[%d] game_color! : %d\n", index, color[index]);
//		}
//
	}
}

char	*search_for_value(char **split_map, char *var_name)
{
	int		array;
	char	**get_texture;
	char	*element_value;

	get_texture = NULL;
	element_value = NULL;
	array = -1;
//	printf("\n----------%s-----------------\n", var_name);
	while(split_map && split_map[++array] && array < 6)
	{
		if (get_texture)
			ftps_free(get_texture);
		get_texture = ft_split(split_map[array], ' ');
		if (!get_texture[2] && ft_strcmp(get_texture[0], var_name) == 0
			&& ft_strcmp(get_texture[1] + (ft_strlen(get_texture[1]) - 4), ".xpm") == 0)
		{
			element_value = ft_strdup(get_texture[1]);
			break ;
		}
	}
	//free get_texture here!
	if (get_texture)
		ftps_free(get_texture);
	return (element_value);
}
