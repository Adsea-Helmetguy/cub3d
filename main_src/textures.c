/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:05:29 by mlow              #+#    #+#             */
/*   Updated: 2024/09/09 12:05:40 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_texture_img(t_game *game, t_img *tmp, char *path)
{
	tmp->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path,
			&(game->texture_size), &(game->texture_size));
	//if (image->img == NULL)
	//	exit_and_free(data, error_msg(ERR_MLX_IMG, 21));
	tmp->addr = (int *)mlx_get_data_addr(tmp->img, &tmp->pixel_bits,
			&tmp->size_line, &tmp->endian);
	return ;
}

static int	*xpm_to_img(t_game *game, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(game, &tmp, path);//tmp is updated here to be used
//	buffer = ft_calloc(1,
//			sizeof * buffer * data->texture_det.size * data->texture_det.size);
	//buffer = malloc(sizeof(int) * (game->texture_size * game->texture_size));
	buffer = malloc(sizeof(int) * (game->texture_size * game->texture_size));
	//if (!buffer)
	//	exit_and_free(data, error_msg(ERR_MALC, 25));
	y = 0;
	while (y < game->texture_size)
	{
		x = 0;
		while (x < game->texture_size)
		{
			buffer[y * game->texture_size + x]
				= tmp.addr[y * game->texture_size + x];
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
	//if (!data->textures)
	//	exit_and_free;
	game->texture_size = 225;//cause my textures are 225 in size
	//north=0,south=1,east=2,west=3,(final)=4(null);
	game->textures[NORTH] = xpm_to_img(game, game->elements.north_texture);
	game->textures[SOUTH] = xpm_to_img(game, game->elements.south_texture);
	game->textures[EAST] = xpm_to_img(game, game->elements.east_texture);
	game->textures[WEST] = xpm_to_img(game, game->elements.west_texture);
	game->textures[4] = NULL;
}
