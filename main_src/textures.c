/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:05:29 by mlow              #+#    #+#             */
/*   Updated: 2024/11/09 17:57:47 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_texture_img(t_game *game, t_img *tmp, char *path)
{
	tmp->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path,
			&(game->texture_width), &(game->texture_height));
	if (tmp->img == NULL)
		close_window_invalidtextures(game);
	tmp->addr = (int *)mlx_get_data_addr(tmp->img, &tmp->pixel_bits,
			&tmp->size_line, &tmp->endian);//issue here
	return ;
}

static int	*xpm_to_img(t_game *game, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(game, &tmp, path);
	//tmp is updated here to be used
//	buffer = ft_calloc(1,
//			sizeof * buffer * data->texture_det.size * data->texture_det.size);
	//buffer = malloc(sizeof(int) * (game->texture_size * game->texture_size));
	buffer = malloc(sizeof(int) * (game->texture_width * game->texture_height));
	//if (!buffer)
	//	exit_and_free(data, error_msg(ERR_MALC, 25));
	y = 0;
	while (y < game->texture_height)
	{
		x = 0;
		while (x < game->texture_width)
		{
			buffer[y * game->texture_height + x]
				= tmp.addr[y * game->texture_height + x];
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
	//if (!game->textures)
	//	exit_and_free;
	game->texture_size = TEXTURE_SIZE;//cause my textures are 225 in size
	//north=0,south=1,east=2,west=3,(final)=4(null);
	game->textures[NORTH] = xpm_to_img(game, game->elements.north_texture);
	game->textures[SOUTH] = xpm_to_img(game, game->elements.south_texture);
	game->textures[EAST] = xpm_to_img(game, game->elements.east_texture);
	game->textures[WEST] = xpm_to_img(game, game->elements.west_texture);
	game->textures[4] = NULL;
}
