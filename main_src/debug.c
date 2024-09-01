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

static void	debug_map(t_data data)
{
	printf("\n-------------------");
	printf("\n****Map details****\n");
	printf("-------------------\n");
	printf("map_w: %d\n", data.map_w);
	printf("map_h: %d\n", data.map_h);
	printf("map_w_in_pixels: %f\n", data.map_w_in_pixels);
	printf("map_h_in_pixels: %f\n", data.map_h_in_pixels);
	printf("PlayerX Location in int: %d\n", data.p_x);
	printf("PlayerY location in int: %d\n", data.p_y);
}

static void	debug_ray(t_player p, t_raycasting ray)
{
	printf("\n-------------------");
	printf("\n****player-Ray****\n");
	printf("-------------------\n");
	printf("value of player.pixel_x: %f\n", p.pixel_x);
	printf("value of player.pixel_y: %f\n", p.pixel_y);
	printf("value of player.plane_x: %f\n", p.plane_x);
	printf("value of player.plane_y: %f\n", p.plane_y);
	printf("Player dir_x: %f\n", p.dir_x);
	printf("Player dir_y: %f\n", p.dir_y);
	printf("Player step_x: %d\n", p.step_x);
	printf("Player step_y: %d\n", p.step_y);
	printf("Player side_dist_x:%f\n", p.sidedir_x);
	printf("Player side_dist_y:%f\n", p.sidedir_y);
	printf("Value of game->ray.deltadist_x: %f\n", ray.deltadist_x);
	printf("Value of game->ray.deltadist_y: %f\n", ray.deltadist_y);
	printf("Value of raydir_x: %f\n", ray.dir_x);
	printf("Value of raydir_y: %f\n", ray.dir_y);
	printf("perpenducular wall distance = %f\n", ray.perpwalldist);
	//printf("multiplier: %f\n", r->multiplier);
	//printf("wall_x: %f\n", r->wall_x);
	//printf("hit_side: %d\n", r->hit_side);
	//printf("line_height: %d\n", r->line_height);
	//printf("draw_start: %d\n", r->draw_start);
	//printf("draw_end: %d\n", r->draw_end);
}

void	debug_check(t_game *game)
{
//	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n");
	//debug_text(game->elements);
	debug_map(game->data);
	debug_ray(game->player, game->ray);
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
//
