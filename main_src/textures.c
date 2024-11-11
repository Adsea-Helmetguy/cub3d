/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:05:29 by mlow              #+#    #+#             */
/*   Updated: 2024/11/11 18:36:08 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// original:
// void	init_texture_img(t_game *game, t_img *tmp, char *path)
void	init_texture_img(t_game *game, t_img *tmp, char *path, int face)
{
	tmp->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path,
			&(game->texture_width[face]), &(game->texture_height[face]));
	if (tmp->img == NULL)
		close_window_invalidtextures(game);
	tmp->addr = (int *)mlx_get_data_addr(tmp->img, &tmp->pixel_bits,
			&tmp->size_line, &tmp->endian);
	// add values for width and height here for the img.
	/*
		# define NORTH 0
		# define SOUTH 1
		# define EAST 2
		# define WEST 3
	*/
	return ;
}

static int	*xpm_img(t_game *game, char *path, int face)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(game, &tmp, path, face);
	buffer = malloc(sizeof(int) * (game->texture_width[face]
				* game->texture_height[face]));
	// if (!buffer)
	//	exit_and_free(data, error_msg(ERR_MALC, 25));
	y = 0;
	while (y < game->texture_width[face])
	{
		x = 0;
		while (x < game->texture_height[face])
		{
			buffer[y * game->texture_height[face] + x] = tmp.addr[y
				* game->texture_height[face] + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(game->mlx.mlx_ptr, tmp.img);
	return (buffer);
}

void	setup_texture(t_game *game)
{
	game->textures = malloc(sizeof(int *) * 5);
	// if (!game->textures)
	//	exit_and_free;
	// north=0,south=1,east=2,west=3,(final)=4(null);
	game->textures[NORTH] = xpm_img(game, game->elements.north_texture, NORTH);
	game->textures[SOUTH] = xpm_img(game, game->elements.south_texture, SOUTH);
	game->textures[EAST] = xpm_img(game, game->elements.east_texture, EAST);
	game->textures[WEST] = xpm_img(game, game->elements.west_texture, WEST);
	game->textures[4] = NULL;
}
