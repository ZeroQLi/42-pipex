/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:39:24 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/12 16:04:20 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char **sploit)
{
	int	i;

	i = 0;
	while(sploit[i])
	{
		free(sploit[i]);
		sploit[i++] = NULL;
	}
	free(sploit);
	sploit = NULL;
}

void free_pip(t_pip *pip)
{	
	if (pip->cmd)
	{
		free(pip->cmd);	 // Free the dynamically allocated command string
		pip->cmd = NULL; // Set to NULL to avoid dangling pointers
	}
	if (pip->args)
	{
		free(pip->args);	 // Free the dynamically allocated command string
		pip->args = NULL; // Set to NULL to avoid dangling pointers
	}
	close(pip->infile);
	close(pip->outfile);
	pip->infile = 0;
	pip->outfile = 0;
	if (pip->invalid_infile)
		unlink(INVALID_FILE);
	pip->invalid_infile = 0;
	free(pip);
	pip = NULL;
}

void	ft_error(t_pip	*pip, int	errno)
{
	if (errno == 0)
	{
		ft_putstr_fd("pipex: invalid arguments\n", 2);
		ft_putstr_fd("usage: ./pipex infile cmd1 outfile cmd2\n", 2);
	}
	else if (errno == -1)
		perror("pipex");
	if (pip != NULL)
		free_pip(pip);
	exit(-1);
}