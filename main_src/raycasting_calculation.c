/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calculation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:19:38 by mlow              #+#    #+#             */
/*   Updated: 2024/08/28 19:14:46 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	raycasting_calculation(t_game *game, int map_x, int map_y)
{
	double	w;
	double	x;
	double	camera_x;

	w = (double)SCREEN_WIDTH;
	x = -1;// or x = -1;
	while (++x < w)
	{
		//calculate ray position and direction
		game->ray.camera_x = 2 * x / w - 1;//x-coordinate in camera space
		camera_x = game->ray.camera_x;
		game->ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		game->ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		//these three thingies below need to while loop!
		player_deltadist_get(game);
		player_sidedist_get(game, map_x, map_y);
		player_dda_get(game);
	}
	return (0);//success if 0!
}

//edit the value SCREEN_HEIGHT or change it to (game->data.map_h * TILE_SIZE)
void	ray_calculate_lineheight(t_game *game, t_player player)
{
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
//
/*
	if (game->ray.hit_side == EAST_WEST_SIDE)
		game->ray.wall_x = player.pixel_y + game->ray.perpwalldist * game->ray.dir_y;
	else
		game->ray.wall_x = player.pixel_x + game->ray.perpwalldist * game->ray.dir_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	//printf("Value of ray.wall_x = %f\n", game->ray.wall_x);
*/
}
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
static void	get_texture_index(t_data *data, t_ray *ray)
{
	if (ray->hit_side == false)
	{
		if (ray->dir_x < 0)
			data->texture_det.index = WEST;
		else
			data->texture_det.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->texture_det.index = SOUTH;
		else
			data->texture_det.index = NORTH;
	}
}

void	update_text_pixels(t_data *data, t_texture_det *tex, t_ray *r, int x)
{
	int			y;
	int			color;

	get_texture_index(data, r);
	tex->x = (int)(r->wall_x * tex->size);
	if ((r->hit_side == false && r->dir_x < 0) || (r->hit_side == true
			&& r->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / r->line_height;
	tex->pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * tex->step;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
}
*/
//
/*
void	raycasting_wall_drawing(t_game *game)
{
}
*/
