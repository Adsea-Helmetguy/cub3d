/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calculation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:19:38 by mlow              #+#    #+#             */
/*   Updated: 2024/09/05 11:16:07 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//look at raycasting_calcuation;
//after mallocing the space for colors at texture_pixeels, 
//now we need to give value to texpos so that we can color them.
/*
void	update_texpos(t_game *game)
{
	int	i;

	i = 0;
}
*/

//edit the value SCREEN_HEIGHT or change it to (game->data.map_h * TILE_SIZE)
static void	ray_calculate_lineheight(t_game *game, t_player player, int x)
{
	int	counter;

	//(void)counter;
	//(void)x;
	//line height
	(void)player;
	game->ray.line_height = (int)(SCREEN_HEIGHT / game->ray.perpwalldist);
	//draw_Start pixel
	game->ray.draw_start = -(game->ray.line_height) / 2 + SCREEN_HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	//draw_End pixel
	game->ray.draw_end = game->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->ray.draw_end >= SCREEN_HEIGHT)
		game->ray.draw_end = SCREEN_HEIGHT - 1;
//
//printf("\n\n\n\n\n\n\n\n\n\n\n\nLine.height= %d\n", game->ray.line_height);
//printf("ray.draw_start= %d\n", game->ray.draw_start);
//printf("ray.draw_end= %d\n", game->ray.draw_end);
//
	printf("X = %d\n", x);
	counter = game->ray.draw_start;
	while (counter < game->ray.draw_end)
	{
		mlxpixel(game, x, counter, 0xa7bed3);
		counter++;
	}
}

int	raycasting_calculation(t_game *game)
{
	int	x;

	//reset_ray(game);
	//reset_player(game);
	x = -1;
	// Clear the screen before redrawing
	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	while (++x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		game->ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x-coordinate in camera space
		game->ray.dir_x = game->player.dir_x + game->player.plane_x * game->ray.camera_x;
		game->ray.dir_y = game->player.dir_y + game->player.plane_y * game->ray.camera_x;
		game->ray.p_x = (int)game->player.p_x;
		game->ray.p_y = (int)game->player.p_y;
		//printf("game->ray.p_x: %d\n", game->ray.p_x);
		//printf("game->ray.p_y: %d\n", game->ray.p_y);
		//these three thingies below need to be in while loop!
		player_deltadist_get(game);
		player_sidedist_get(game);
		player_dda_get(game);
		ray_calculate_lineheight(game, game->player, x);
		//these three thingies above need to be in while loop!
		//update_texpos(d, &d->texture_det, &d->ray, d->view.x);
	}
	return (0);//success if 0!
}
//
//0x00FF0000
//means A = 00, R = FF, G = 00 & B = 00.
int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

//https://github.com/gleal42/cub3d?tab=readme-ov-file
/*
int	render_frame(t_game *game)
{
	int	color_of_texture;
	int	width;
	int	height;

	color_of_texture = 0;
	game->pink_cube.addr = (int *)mlx_get_data_addr(game->pink_cube.img_ptr \
		, &game->pink_cube.bitsinpixel, &game->pink_cube.line_bytes \
		, &game->pink_cube.endian);
	color_of_texture = create_trgb(0, 255, 218, 233);//== 0x00ffdae9
	height = 0;
	while (height < 3)
	{
		width = 0;
		while (width < 3)
		{
			game->pink_cube.addr[height * 3 + width] = color_of_texture;
			width++;
		}
		height++;
	}
	return (0);
}
*/
//
//
//
/*
void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

int	render_frame(t_data *d)
{
	d->view.y = 0;
	while (d->view.y < HEIGHT)
	{
		d->view.x = 0;
		while (d->view.x < WIDTH)
		{
			if (d->texture_pixels[d->view.y][d->view.x] > 0)
				d->view.color = d->texture_pixels[d->view.y][d->view.x];
			else if (d->view.y < HEIGHT / 2)
				d->view.color = d->texture_det.hex_ceiling;
			else if (d->view.y < HEIGHT - 1)
				d->view.color = d->texture_det.hex_floor;
			set_image_pixel(&d->view.screen, d->view.x, \
			d->view.y, d->view.color);
			d->view.x++;
		}
		d->view.y++;
	}
	return (SUCCESS);
}
*/
//
/*
////v1
		counter = draw_start
		while (counter < draw_end)
		{
			mlxpixel(counter);
			counter++;
		}
		////
		////
*/
//
/*
	////v2
	counter = 0;
	while (counter < game->ray.line_height)
	{
		mlxpixel(game, x, SCREEN_HEIGHT/2 + counter, 0x00FF0000);
		mlxpixel(game, x, SCREEN_HEIGHT/2 - counter, 0x00FF0000);
		counter++;
	}
*/