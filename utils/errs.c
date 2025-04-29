/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:39:24 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/19 14:28:50 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char **sploit)
{
	int	i;

	i = 0;
	while (sploit[i])
	{
		free(sploit[i]);
		sploit[i++] = NULL;
	}
	free(sploit);
	sploit = NULL;
}

void	free_pip(t_pip *pip)
{
	if (pip->cmd)
		free(pip->cmd);
	if (pip->args)
		free(pip->args);
	if (pip->infile != -1)
		close(pip->infile);
	if (pip->infile != -1)
		close(pip->outfile);
	if (pip->invalid_infile)
		unlink(INVALID_FILE);
	pip->args = NULL;
	pip->cmd = NULL;
	pip->infile = 0;
	pip->outfile = 0;
	pip->invalid_infile = 0;
	free(pip);
	pip = NULL;
}

void	ft_error(t_pip *pip, int errno)
{
	if (errno == 0)
	{
		ft_putstr_fd("pipex: invalid arguments\n", 2);
		ft_putstr_fd("usage: ./pipex infile cmd1 outfile cmd2\n", 2);
	}
	else if (errno == 1)
		ft_putstr_fd("pipex: permission denied:\n", 2);
	else if (errno == 2)
		ft_putstr_fd("pipex: error creating fork:\n", 2);
	else if (errno == 3)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(pip->cmd, 2);
	}
	else if (errno == -1)
		perror("pipex");
	if (pip != NULL)
		free_pip(pip);
	exit(-1);
}
