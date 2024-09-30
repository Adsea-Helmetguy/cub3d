/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:13:22 by mlow              #+#    #+#             */
/*   Updated: 2023/12/06 00:19:16 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_msg(char *message, int exit_code)
{
	if (exit_code != 0)
	{
		ft_putstr_fd("\n--------exitcode != 0--------\n", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd("-------------bad-------------\n", 2);
		exit(exit_code);
	}
	else
	{
		ft_putstr_fd("\n--------exitcode = 0--------\n", 1);
		ft_putstr_fd(message, 1);
		ft_putstr_fd("------------good------------\n", 1);
		exit(exit_code);
	}
}
