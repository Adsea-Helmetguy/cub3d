/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_value_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:39:08 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 18:35:57 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static char	*search_for_color(char **split_map, char *var_name)
{
	int		array;
	char	**get_color;
	char	*element_color;

	get_color = NULL;
	element_color = NULL;
	array = -1;
	while (split_map && split_map[++array] && array < 6)
	{
		if (get_color)
			ftps_free(get_color);
		get_color = ft_split(split_map[array], ' ');
		if (!get_color || !get_color[1] || !get_color[0])
			continue ;
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

static int	obtain_color(char **map, char *var_name, t_getcolor *get)
{
	get->game_color = NULL;
	get->element_color = search_for_color(map, var_name);
	if (!get->element_color)
	{
		printf("Error: Color for %s not found in map file\n", var_name);
		return (1);
	}
	get->game_color = ft_split(get->element_color, ',');
	free(get->element_color);
	if (!(get->game_color))
	{
		printf("Error: Failed to split the color values\n");
		return (1);
	}
	get->array = -1;
	get->all_digits = 1;
	return (0);
}

static void	check_obtained_color(char *var_name, t_getcolor *get)
{
	while (get->game_color && get->game_color[++(get->array)])
	{
		get->index = -1;
		printf("for %s\n", var_name);
		while (get->game_color[get->array][++(get->index)])
		{
			if (ft_isdigit(get->game_color[get->array][get->index]) == 0)
			{
				get->all_digits = 0;
				break ;
			}
		}
		if (!(get->all_digits) || (get->array) >= 3)
		{
			get->all_digits = 0;
			break ;
		}
		get->before_mod = ft_atoi(get->game_color[get->array]);
		get->before_mod %= 256;
		get->rgb_colors = ft_itoa(get->before_mod);
		printf("get->after_mod value in string: %s\n", get->rgb_colors);
		free(get->game_color[get->array]);
		get->game_color[get->array] = ft_strdup(get->rgb_colors);
		free(get->rgb_colors);
	}
}

int	getting_color(char **map, char *var_name, int color[3])
{
	t_getcolor	get;

	if (obtain_color(map, var_name, &get) != 0)
		return (1);
	check_obtained_color(var_name, &get);
	if (get.all_digits == 0)
	{
		if (get.game_color)
			ftps_free(get.game_color);
		return (1);
	}
	if (get.game_color && get.all_digits)
	{
		get.array = -1;
		get.index = -1;
		while (get.game_color && get.game_color[++(get.array)])
			color[++(get.index)] = ft_atoi(get.game_color[get.array]);
	}
	if (get.game_color)
		ftps_free(get.game_color);
	return (0);
}

char	*search_for_value(char **split_map, char *var_name)
{
	int		array;
	char	**get_texture;
	char	*element_value;

	get_texture = NULL;
	element_value = NULL;
	array = -1;
	while (split_map && split_map[++array] && array < 6)
	{
		if (get_texture)
			ftps_free(get_texture);
		get_texture = ft_split(split_map[array], ' ');
		if (!get_texture[2] && ft_strcmp(get_texture[0], var_name) == 0
			&& ft_strcmp(get_texture[1] + (ft_strlen(get_texture[1]) - 4),
				".xpm") == 0)
		{
			element_value = ft_strdup(get_texture[1]);
			break ;
		}
	}
	if (get_texture)
		ftps_free(get_texture);
	return (element_value);
}
