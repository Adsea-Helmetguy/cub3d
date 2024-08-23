/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:57:18 by mlow              #+#    #+#             */
/*   Updated: 2024/08/21 13:19:39 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
//################################################################################//
//############################## THE MOUVEMENT CODE ##############################//
//################################################################################//

void	player_sidedist_get(t_game *game, int map_x, int map_y)
{
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;

	rayDirX = game->player.raydir_x;
	rayDirY = game->player.raydir_y;
	deltaDistX = game->player.raydir_x;
	deltaDistY = game->player.raydir_y;
	if (rayDirX < 0)
	{
		game->player.step_x = -1;
		game->player.sidedir_x = (game->player.pixel_x - map_x) * deltaDistX;
	}
	else if (rayDirX > 0)
	{
		game->player.step_x = 1;
		game->player.sidedir_x = (map_x + 1 - game->player.pixel_x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		game->player.step_y = -1;
		game->player.sidedir_y = (game->player.pixel_y - map_y) * deltaDistY;
	}
	else if (rayDirY > 0)
	{
		game->player.step_y = 1;
		game->player.sidedir_y = (map_y + 1 - game->player.pixel_y) * deltaDistY;
	}
}


void	player_deltadist_get(t_game *game)
{
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;

	rayDirX = game->player.raydir_x;
	rayDirY = game->player.raydir_y;
	deltaDistX = 0;
	deltaDistY = 0;
	if (rayDirX == 0)
		deltaDistX = 1e30;
	else if (rayDirX != 0)
		deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
	if (rayDirY == 0)
		deltaDistY = 1e30;
	else if (rayDirY != 0)
		deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
	game->player.raydir_x = deltaDistX;
	game->player.raydir_y = deltaDistY;
	if (deltaDistX == 1e30)
		game->player.raydir_x = 0;
	if (deltaDistY == 1e30)
		game->player.raydir_y = 0;
	printf("Value of deltaDistX: %f\n", game->player.raydir_x);
	printf("Value of deltaDistY: %f\n", game->player.raydir_y);
}


void	player_raydir_get(t_game *game)
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	w;
	double	x;

	w = (double)SCREEN_WIDTH;
	printf("Value of w: %f\n", w);
	x = game->player.pixel_x - 1;// or x = -1;
	while (++x < w)
	{
		//calculate ray position and direction
		camera_x = 2 * game->player.pixel_x / w - 1;//x-coordinate in camera space
		raydir_x = game->player.dir_x + game->player.plane_x * camera_x;
		raydir_y = game->player.dir_y + game->player.plane_y * camera_x;
	}
	game->player.raydir_x = raydir_x;
	game->player.raydir_y = raydir_y;
	printf("Value of x: %f\n", x);
	printf("Value of raydir_x: %f\n", game->player.raydir_x);
	printf("Value of raydir_y: %f\n", game->player.raydir_y);
}

void	player_set_direction(t_game *game)
{
	if (game->player.direction == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_y = -0.66;
	}
	if (game->player.direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_x = 0.66;
	}
	if (game->player.direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_x = -0.66;
	}
	if (game->player.direction == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_y = 0.66;
	}
	printf("Player_direction = %c\n", game->player.direction);
	printf("Plane_x: %f\n", game->player.plane_x);
	printf("Plane_y: %f\n", game->player.plane_y);
}





























/*
void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx) // release the key
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
}

void	mlx_key(mlx_key_data_t keydata, void *ml) // key press
{
	t_mlx *mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
		ft_exit(mlx);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
		mlx->ply->l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
		mlx->ply->l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
		mlx->ply->u_d = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
		mlx->ply->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
		mlx->ply->rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
		mlx->ply->rot = 1;
	ft_reles(keydata, mlx); // release the key
}

void	rotate_player(t_mlx *mlx, int i) // rotate the player
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED; // rotate right
		if (mlx->ply->angle > 2 * M_PI)
			mlx->ply->angle -= 2 * M_PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED; // rotate left
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * M_PI;
	}
}

void	move_player(t_mlx *mlx, double move_x, double move_y) // move the player
{
	int  map_grid_y;
	int  map_grid_x;
	int  new_x;
	int  new_y;

	new_x = roundf(mlx->ply->plyr_x + move_x); // get the new x position
	new_y = roundf(mlx->ply->plyr_y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' && \
	(mlx->dt->map2d[map_grid_y][mlx->ply->plyr_x / TILE_SIZE] != '1' && \
	mlx->dt->map2d[mlx->ply->plyr_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		mlx->ply->plyr_x = new_x; // move the player
		mlx->ply->plyr_y = new_y; // move the player
	}
}

void hook(t_mlx *mlx, double move_x, double move_y) // hook the player
{
	if (mlx->ply->rot == 1) //rotate right
		rotate_player(mlx, 1);
	if (mlx->ply->rot == -1) //rotate left
		rotate_player(mlx, 0);
	move_player(mlx, move_x, move_y); // move the player
}
*/
