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
		write(exit_code, "--------exit--------\n", 21);
		perror(message);
		printf("exitcode == 1!!\n");
		write(exit_code, "--------exit--------\n", 21);
		exit(exit_code);
	}
	else
	{
		write(exit_code, "--------good--------\n", 21);
		printf("%s", message);
		write(exit_code, "--------good--------\n", 21);
		exit(exit_code);
	}
}
