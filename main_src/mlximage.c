/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlximage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:08:11 by mlow              #+#    #+#             */
/*   Updated: 2024/08/17 17:08:23 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	mlximage_on_screen(t_game *game)
{
	int	size;
	void	*img;

	size = 10;
	img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, game->elements.south_texture, &size, &size);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, img, 20, 20);
	// the location of where to put the image can be changed, right now i put it as
	//20, 20(x, y);
}
