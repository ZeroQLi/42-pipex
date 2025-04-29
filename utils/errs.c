/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:06:12 by mtangalv          #+#    #+#             */
/*   Updated: 2025/04/27 17:05:58 by mtangalv         ###   ########.fr       */
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
	if (pip->outfile != -1)
		close(pip->outfile);
	pip->args = NULL;
	pip->cmd = NULL;
	pip->infile = 0;
	pip->outfile = 0;
	free(pip);
	pip = NULL;
}

void	ft_error(t_pip *pip, int errno)
{
	if (pip)
		free_pip(pip);
	if (errno == 0)
	{
		ft_putstr_fd("pipex: Invalid arguments\n", 2);
		ft_putstr_fd("usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	}
	else if (errno == 1)
		ft_putstr_fd("pipex: Permission denied\n", 2);
	else if (errno == 2)
		ft_putstr_fd("pipex: Error creating fork\n", 2);
	else if (errno == 3)
	{
		ft_putstr_fd("pipex: Command not found\n", 2);
		exit(127);
	}
	else if (errno == -1)
		perror("pipex");
	exit(1);
}
