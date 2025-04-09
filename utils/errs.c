/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:39:24 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/09 10:49:25 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(int	errno)
{
	if (errno == 0)
		ft_printf("pipex: invalid arguments\n");
	else if (errno == 1)
		ft_printf("pipex: no such file\n");
	else if (errno == 2)
		ft_printf("pipex: permission denied\n");
	ft_printf("usage: ./pipex infile cmd1 outfile cmd2\n");
	exit(-1);
}