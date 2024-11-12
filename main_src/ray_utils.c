/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:19:37 by cwijaya           #+#    #+#             */
/*   Updated: 2024/11/12 15:52:54 by cwijaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	nor_angle(double angle)
{
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	x_positive(double angle)
{
	if (angle >= M_PI / 2 && angle <= 3 * (M_PI / 2))
		return (0);
	return (1);
}

int	y_positive(double angle)
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

int	init_h(double angle, double *x_step, double *y_step, double *y_intercept)
{
	int	adjust;

	adjust = 0;
	*y_step = TILE_SIZE;
	if (y_positive(angle))
		*y_intercept += TILE_SIZE;
	else
	{
		adjust = -1;
		*y_step = -TILE_SIZE;
	}
	*x_step = TILE_SIZE / tan(angle);
	if ((!x_positive(angle) && *x_step > 0) || (x_positive(angle)
			&& *x_step < 0))
		*x_step *= -1;
	return (adjust);
}

int	init_v(double angle, double *x_step, double *y_step, double *x_intercept)
{
	int	adjust;

	adjust = 0;
	*x_step = TILE_SIZE;
	if (x_positive(angle))
		*x_intercept += TILE_SIZE;
	else
	{
		adjust = -1;
		*x_step = -TILE_SIZE;
	}
	*y_step = TILE_SIZE * tan(angle);
	if ((!y_positive(angle) && *y_step > 0) || (y_positive(angle)
			&& *y_step < 0))
		*y_step *= -1;
	return (adjust);
}
