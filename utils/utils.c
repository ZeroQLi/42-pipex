/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:05:57 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/02 19:23:32 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_infile(char *file)
{
	int	fd;

	fd = -1;
	if (access(file, R_OK) == -1)
		perror("pipex");
	else
		fd = open(file, O_RDONLY, 420);
	return (fd);
}

int	open_outfile(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		perror("pipex");
	return (fd);
}

t_pip	*init_pipex(void)
{
	t_pip	*pip;

	pip = malloc(sizeof(t_pip));
	if (!pip)
		exit(-1);
	pip->cmd = NULL;
	pip->args = NULL;
	pip->infile = -1;
	pip->outfile = -1;
	return (pip);
}
