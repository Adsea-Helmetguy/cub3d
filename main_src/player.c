/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:57:18 by mlow              #+#    #+#             */
/*   Updated: 2024/08/31 15:55:33 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
//################################################################################//
//############################## THE MOUVEMENT CODE ##############################//
//################################################################################//

//
/*
void	player_dda_get(t_game *game, int map_x, int map_y)
{
	double	deltaDistX;
	double	deltaDistY;
	double		line;

	(void)map_x;
	(void)map_y;
	deltaDistX = game->ray.deltadist_x;
	deltaDistY = game->ray.deltadist_y;
	game->ray.p_x = game->player.p_x;
	game->ray.p_y = game->player.p_y;
	game->ray.perpwalldist = 0;
	line = 0;
	while (1)
	{
		//jump to next map square, either in x-direction, or in y-direction
		//if sideDistX finds the end width of the box first
		if (game->player.sidedir_x < game->player.sidedir_y)
		{
			game->player.sidedir_x += deltaDistX;
			game->ray.p_x += game->player.step_x;
			game->ray.hit_side = EAST_WEST_SIDE;
		}
		else//if sideDistY finds the end height of the box first
		{
			game->player.sidedir_y += deltaDistY;
			game->ray.p_y += game->player.step_y;
			game->ray.hit_side = NORTH_SOUTH_SIDE;
		}
		if (game->ray.p_y < 0 || game->ray.p_x < 0 
			|| !(game->data.map2d[game->ray.p_y])
			|| !(game->data.map2d[game->ray.p_y][game->ray.p_x]))
			break ;
		if (game->data.map2d[game->ray.p_y][game->ray.p_x] == '1')
			break ;
	}
	if (game->ray.hit_side == EAST_WEST_SIDE)
		game->ray.perpwalldist = (game->player.sidedir_x - deltaDistX);
	else
		game->ray.perpwalldist = (game->player.sidedir_y - deltaDistY);
}
*/
//
void	player_dda_get(t_game *game)
{
	double	deltaDistX;
	double	deltaDistY;

	deltaDistX = game->ray.deltadist_x;
	deltaDistY = game->ray.deltadist_y;
	//game->ray.perpwalldist = 0;
	while (1)
	{
		//jump to next map square, either in x-direction, or in y-direction
		//if sideDistX finds the end width of the box first
		if (game->player.sidedir_x < game->player.sidedir_y)
		{
			game->player.sidedir_x += deltaDistX;
			game->ray.p_x += game->player.step_x;
			game->ray.hit_side = EAST_WEST_SIDE;
		}
		else//if sideDistY finds the end height of the box first
		{
			game->player.sidedir_y += deltaDistY;
			game->ray.p_y += game->player.step_y;
			game->ray.hit_side = NORTH_SOUTH_SIDE;
		}
		if (game->ray.p_y < 0 || game->ray.p_x < 0 //HEIGHT AND WIDTH OF MAP EDIT THIS!!
			|| game->ray.p_y >= game->data.map_h || game->ray.p_x >= game->data.map_w)
			break ;
		if (game->data.map2d[game->ray.p_y][game->ray.p_x] == '1')
			break ;
	}
	if (game->ray.hit_side == EAST_WEST_SIDE)
		game->ray.perpwalldist = (game->player.sidedir_x - deltaDistX);
	else
		game->ray.perpwalldist = (game->player.sidedir_y - deltaDistY);
	if (game->ray.perpwalldist <= 0)
		printf("game->ray.perpwalldist: %f", game->ray.perpwalldist);
}

void	player_sidedist_get(t_game *game)
{
	double	deltaDistX;
	double	deltaDistY;

	deltaDistX = game->ray.deltadist_x;
	deltaDistY = game->ray.deltadist_y;
	if (game->ray.dir_x < 0)
	{
		game->player.step_x = -1;
		game->player.sidedir_x = ((game->player.pixel_x / TILE_SIZE) - game->ray.p_x) * deltaDistX;
	}
	else
	{
		game->player.step_x = 1;
		game->player.sidedir_x = (game->ray.p_x + 1.0 - (game->player.pixel_x / TILE_SIZE)) * deltaDistX;
	}
	if (game->ray.dir_y < 0)
	{
		game->player.step_y = -1;
		game->player.sidedir_y = ((game->player.pixel_y / TILE_SIZE) - game->ray.p_y) * deltaDistY;
	}
	else
	{
		game->player.step_y = 1;
		game->player.sidedir_y = (game->ray.p_y + 1.0 - (game->player.pixel_y / TILE_SIZE)) * deltaDistY;
	}
}

void	player_deltadist_get(t_game *game)
{
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;

	rayDirX = game->ray.dir_x;
	rayDirY = game->ray.dir_y;
	if (rayDirX == 0)
		deltaDistX = 1e30;
	else
		deltaDistX = fabs(1.0 / rayDirX);
	if (rayDirY == 0)
		deltaDistY = 1e30;
	else
		deltaDistY = fabs(1.0 / rayDirY);
	game->ray.deltadist_x = deltaDistX;
	game->ray.deltadist_y = deltaDistY;
}

void	player_set_direction(t_game *game)
{
	if (game->player.direction == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
	}
	if (game->player.direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = 0.66;
	}
	if (game->player.direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = -0.66;
	}
	if (game->player.direction == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
	}
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
