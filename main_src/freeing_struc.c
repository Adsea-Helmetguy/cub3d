/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_struc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:07:31 by mlow              #+#    #+#             */
/*   Updated: 2024/07/18 20:34:17 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ftps_free(char **to_free)
{
	int	array;

	array = 0;
	if (!to_free)
		return ;
	while (to_free[array])
	{
		free(to_free[array]);
		to_free[array] = NULL;
		array++;
	}
	free(to_free);
	to_free = NULL;
}

void	free_textures(int **game_textures)
{
    int index;

	index = 0;
	if (!game_textures)
		return ;
    while (index < 4) //Free (NORTH, SOUTH, EAST, WEST)
    {
        if (game_textures[index])
            free(game_textures[index]);
        index++;
    }
    if (game_textures)
        free(game_textures); //Free the array with texture pointers
}
/*
void	free_env(t_mini *mini)
{
	t_env	*env_tmp;

	while (mini->envpmen)
	{
		env_tmp = mini->envpmen->next;
		ftps_free(mini->envpmen->user_value);
		if (mini->envpmen->name)
			free(mini->envpmen->name);
		if (mini->envpmen->value)
			free(mini->envpmen->value);
		free(mini->envpmen);
		mini->envpmen = env_tmp;
	}
}

void	free_struc_mini(t_mini *mini)
{
	free_env(mini);
	if (mini->dollar_string)
	{
		free(mini->dollar_string);
		mini->dollar_string = NULL;
	}
}
*/
