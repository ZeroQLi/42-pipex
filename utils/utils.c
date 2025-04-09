/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:29:07 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/09 10:54:28 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_file(char *path, int in_out)
{
	int	fd;
	if (in_out == 0)
	{
		if (access(path, F_OK) == -1)
			ft_error(1);
		if (access(path, R_OK) == -1)
			ft_error(2);
	}
	else
	{
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			ft_error(2);
		close(fd);
	}
}