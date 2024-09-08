/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:25:37 by mlow              #+#    #+#             */
/*   Updated: 2024/09/05 10:40:38 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
static int	render_image(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (game->texture_pixels[y][x] > 0)
			{
				color = game->texture_pixels[y][x];
				mlxpixel(game, x, y, color);
			}
			x++;
		}
		y++;
	}
	return (0);
}
*/

static void	init_texture_pixels(t_game * game)
{
	int	i;

	//if (game->texture_pixels)
	//	free_textures();
	game->texture_pixels = malloc(sizeof(int *) * SCREEN_HEIGHT + 1);
	//if (!data->texture_pixels)
	//	exit_and_free(data, error_msg(ERR_MALC, 23));
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		game->texture_pixels[i] = malloc(sizeof(int *) * SCREEN_WIDTH + 1);
		//if (!game->texture_pixels[i])
		//	exit_and_free(data, error_msg(ERR_MALC, 24));
		i++;
	}
}

int	mixpixel_render(t_game *game)
{
	init_texture_pixels(game); //drawing the texture first before game
	draw_background(game);
	raycasting_calculation(game);
	//draw_display(game);
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
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, SCREEN_HEIGHT, SCREEN_WIDTH);
	//if (game->mlx.img_ptr == NULL)
	//	exit_and_free(data, error_msg(ERR_MLX_IMG, 20));
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bits_per_pixel,
				&game->mlx.line_length, &game->mlx.endian);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img_ptr, 0, 0);
}