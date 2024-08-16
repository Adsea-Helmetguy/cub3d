/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:03:45 by mlow              #+#    #+#             */
/*   Updated: 2023/12/06 00:20:26 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
void	end_exit(char *message, int exit_code, t_game *game)
{
	int	array;

	if (exit_code == 2)
	{
		array = -1;
		if (game->map.row)
		{
			while (game->map.row[++array])
				free(game->map.row[array]);
			free(game->map.row);
		}
		array = -1;
		if (game->map.grid)
		{
			while (game->map.grid[++array])
				free(game->map.grid[array]);
			free(game->map.grid);
		}
		exit_code = 1;
	}
	close(game->map.fd);
	print_message(message, exit_code);
}
*/
void	end_exit(char *message, int exit_code, t_game *game)
{
	(void)game;
	//close(game->data.fd);
	print_msg(message, exit_code);
}

void	free_end_exit(char *message, int exit_code, t_game *game, char **str)
{
	if (str && *str)
	{
		free(*str);
		str = NULL;
	}
	if (game->elements.north_texture)
		free(game->elements.north_texture);
	if (game->elements.south_texture)
		free(game->elements.south_texture);
	if (game->elements.west_texture)
		free(game->elements.west_texture);
	if (game->elements.east_texture)
		free(game->elements.east_texture);
	if (game->data.map2d)
		ftps_free(game->data.map2d);
	end_exit(message, exit_code, game);
}

/*
int	x_close_window(t_game *game)
{
	int	array;

	array = -1;
	if (game->map.row)
	{
		while (game->map.row[++array])
			free(game->map.row[array]);
		free(game->map.row);
	}
	array = -1;
	if (game->map.grid)
	{
		while (game->map.grid[++array])
			free(game->map.grid[array]);
		free(game->map.grid);
	}
	free_sprites(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	end_exit("Quitting game.\n", 0, game);
	return (0);
}

void	free_sprites(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->map.coin);
	mlx_destroy_image(game->mlx_ptr, game->map.wall);
	mlx_destroy_image(game->mlx_ptr, game->player.start);
	mlx_destroy_image(game->mlx_ptr, game->map.empty);
	mlx_destroy_image(game->mlx_ptr, game->map.door_exit);
}

void	*game_checkerror_exit(char *message, t_game *game)
{
	if (game->map.error_code != 0)
	{
		ft_printf("ERROR!! ");
		ft_printf("%s", message);
		ft_printf(" error_code != 0\n");
		return (NULL);
	}
}
*/
