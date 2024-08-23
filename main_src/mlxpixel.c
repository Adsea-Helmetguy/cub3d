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
int	render_images(t_data *data)
{
	init_texture_pixels(data);
	calc_raycast(data);
	render_frame(data);
	mlx_put_image_to_window(data->view.mlx, data->view.win, \
	data->view.screen.img, 0, 0);
	return (0);
}
*/
int	mixpixel_render(t_game *game)
{
	//redraw_player(game);
	draw_display(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img_ptr, 0, 0);
	return (0);
}


void	mlxpixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->mlx.addr + (y * game->mlx.line_length + x * (game->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//int offset = (y * line_length + mx * (bits_per_pixel / 8)); //use this in future
void	mlxpixel_on_screen(t_game *game)
{
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, 1900, 1000);
	//Now, we have an image but no pixels
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bits_per_pixel,
				&game->mlx.line_length, &game->mlx.endian);
	//Now we have the image address, but still no pixels.
	//cause bytes are not aligned, line_length differs from window width.
	//mlx_loop_hook()
	//function display draw everything
	draw_display(game);
	//mlxpixel(game, 500, 500, 0x00FF0000);//wait when does this happen/used???
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img_ptr, 0, 0);
}
