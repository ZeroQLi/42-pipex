/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:39:24 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/10 00:52:09 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_pip(t_pip *pip)
{
	pip->cmd = NULL;
	pip->arg = NULL;
	pip->in_fd = 0;
	pip->out_fd = 0;
	pip->invalid_infile = 0;
	free(pip);
	pip = NULL;
}

void	ft_error(t_pip	*pip, int	errno)
{
	if (errno == 0)
		ft_printf("pipex: invalid arguments\n");
	else if (errno == 1)
		ft_printf("pipex: no such file\n");
	else if (errno == 2)
		ft_printf("pipex: permission denied\n");
	else if (errno == -1)
		ft_printf("pipex: an unknown error occured\n");
	if (pip != NULL)
		free_pip(pip);
	ft_printf("usage: ./pipex infile cmd1 outfile cmd2\n");
	exit(-1);
}