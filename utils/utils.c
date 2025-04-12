/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:29:07 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/12 23:51:52 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_infile(t_pip *pip, char *file)
{
	int	fd;

	if (access(file, R_OK) == -1)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(file, 2);
		fd = open(INVALID_FILE, O_CREAT | O_RDONLY, 0644);
		pip->invalid_infile = 1;
	}
	else
		fd = open(file, O_RDONLY);
	return (fd);
}

int	open_outfile(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	return (fd);
}

int	init_files(t_pip *pip, char *argv[])
{
	pip->infile = open_infile(pip, argv[1]);
	if (pip->infile == -1)
		return (-1);
	pip->outfile = open_outfile(argv[4]);
	if (pip->outfile == -1)
		return (-1);
	return (0);
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
	pip->invalid_infile = 0;
	return (pip);
}
