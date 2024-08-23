/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:28:01 by mlow              #+#    #+#             */
/*   Updated: 2024/08/23 14:28:22 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	debug_ray(t_player r)
{
	printf("\n****player-Ray****\n");
	//printf("multiplier: %f\n", r->multiplier);
	printf("dir_x: %f\n", r.dir_x);
	printf("dir_y: %f\n", r.dir_y);
	printf("step_x: %d\n", r.step_x);
	printf("step_y: %d\n", r.step_y);
	printf("side_dist_x:%f\nside_dist_y:%f\n", r.sidedir_x, r.sidedir_y);
	//printf("delta_dist_x: %f\n", r->delta_dist_x);
	//printf("delta_dist_y: %f\n", r->delta_dist_y);
	//printf("perp_dist: %f\n", r->perp_dist);
	//printf("wall_x: %f\n", r->wall_x);
	//printf("hit_side: %d\n", r->hit_side);
	//printf("line_height: %d\n", r->line_height);
	//printf("draw_start: %d\n", r->draw_start);
	//printf("draw_end: %d\n", r->draw_end);
}

//
/*
static void	debug_text(t_element e)
{
	printf("\n****Texture****\n");
	printf("North Path: %s\n", e.north_texture);
	printf("South Path: %s\n", e.south_texture);
	printf("East Path: %s\n", e.east_texture);
	printf("West Path: %s\n", e.west_texture);
	printf("floor: %i, %i, %i\n", e.floor_color[0], e.floor_color[1], e.floor_color[2]);
	printf("ceil: %i, %i, %i\n", e.ceiling_color[0], e.ceiling_color[1], e.ceiling_color[2]);
	//printf("hex_floor: %ld\n", elements->hex_floor);
	//printf("hex_ceiling: %ld\n", elements->hex_ceiling);
	//printf("index: %i\n", elements->index);
	//printf("step: %f\n", elements->step);
}
*/

static void	debug_player(t_player p)
{
	printf("\n****Player****\n");
	//printf("dir: %c\n", p.dir);
	printf("pixel_x: %f\n", p.pixel_x);
	printf("pixel_y: %f\n", p.pixel_y);
	printf("dir_x: %f\n", p.dir_x);
	printf("dir_y: %f\n", p.dir_y);
	printf("plane_x: %f\n", p.plane_x);
	printf("plane_y: %f\n", p.plane_y);
	//printf("move_x: %d\n", p.move_x);
	//printf("move_y: %d\n", p.move_y);
	//printf("has_moved: %d\n", p.has_moved);
	printf("rotate: %d\n", p.rotation);
}

void	debug_check(t_game *game)
{
	//debug_text(game->elements);
	debug_player(game->player);
	debug_ray(game->player);
}
