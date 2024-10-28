/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:25:37 by mlow              #+#    #+#             */
/*   Updated: 2024/08/12 14:18:54 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
*/
//
//

//focus on is:
/*
	the line height of the vertical lines drawn on the screen needs to go beyond the screen.
	so that the walls won't be facing to you.
*/
void	mlxpixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
		return ;
	dst = game->mlx.addr + (y * game->mlx.line_length + x * (game->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//int offset = (y * line_length + mx * (bits_per_pixel / 8)); //use this in future
void	mlxpixel_on_screen(t_game *game)
{
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->mlx.img_ptr)
	{
		game->error_code = 1;
 		return ;// or call your exit_and_free function here
	}
	//(after mlx_new_image)Now, we have an image but no pixels
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bits_per_pixel,
				&game->mlx.line_length, &game->mlx.endian);
	if (!game->mlx.addr)
	{
		game->error_code = 1;
 		return ;// or call your exit_and_free function here
	}
	//(after mlx_get_data_addr)Now we have the image address, but still no pixels.
	//cause bytes are not aligned, line_length differs from window width.
	//mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img_ptr, 0, 0);
}
