/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:29:07 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/10 01:04:06 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int open_infile(t_pip *pip, char *file)
{
	int	fd;
	if (access(file, R_OK) == -1)
	{
		perror("./pipex");
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

	t_pip *init_pipex(void)
{
	t_pip	*pip;

	pip = malloc(sizeof(t_pip));
	if (!pip)
		exit(-1);
	pip->cmd = "/bin/cat";
	pip->arg = NULL;
	pip->in_fd = -1;
	pip->out_fd = -1;
	pip->invalid_infile = 0;
	return (pip);
}