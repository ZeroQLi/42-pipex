/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:18:15 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/10 01:04:44 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	execute(t_pip *pip)
{
	char	*args[2];

	args[0] = pip->cmd;
	args[1] = pip->arg;
	execve(pip->cmd, args, NULL);
}

static void	run_child(t_pip *pip, char *argv[])
{
	int	fd;
	
	fd = open_infile(pip, argv[1]);
	if (fd == -1)
		ft_error(pip, -1);
	dup2(fd, STDIN_FILENO);
	dup2(pip->in_fd, STDOUT_FILENO);
	close(pip->out_fd);
	execute(pip);
}

static void run_parent(t_pip *pip, char *argv[])
{
	int	fd;

	fd = open_outfile(argv[3]);
	if (fd == -1)
		ft_error(pip, -1);
	dup2(fd, STDOUT_FILENO);
	dup2(pip->out_fd, STDIN_FILENO);
	close(pip->in_fd);
	execute(pip);
}

	int main(int argc, char *argv[])
{
	int		pipe_fds[2];
	pid_t	pid;
	t_pip	*pip;

	if (argc != 5)
		ft_error(NULL, 0);
	pip = init_pipex();
	if (pipe(pipe_fds) == -1)
		ft_error(pip, -1);
	pip->in_fd = pipe_fds[1];
	pip->out_fd = pipe_fds[0];
	pid = fork();
	if (pid == -1)
		ft_error(pip, -1);
	if (!pid)
		run_child(pip, argv);
	wait(0);
	run_parent(pip, argv);
	return (0);
}