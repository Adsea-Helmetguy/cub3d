/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwijaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:19:37 by cwijaya           #+#    #+#             */
/*   Updated: 2024/11/11 18:31:44 by cwijaya          ###   ########.fr       */
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
