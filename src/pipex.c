/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:18:15 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/12 23:48:41 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	execute(t_pip *pip, char *cmd, char **envs)
{
	if (!cmd[0])
		ft_error(pip, 1);
	if (parse_commands(pip, cmd, envs) == -1)
		return (-1);
	if (execve(pip->cmd, pip->args, envs) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(pip->cmd, 2);
		free_pip(pip);
		exit(-1);
	}
	return (0);
}

static int	run_child(t_pip *pip, char *argv[], int *pipe_fds, char **envs)
{
	dup2(pip->infile, STDIN_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[0]);
	close(pip->infile);
	close(pip->outfile);
	close(pipe_fds[1]);
	if (execute(pip, argv[2], envs) == -1)
		return (-1);
	return (0);
}

static int	run_parent(t_pip *pip, char *argv[], int	*pipe_fds, char **envs)
{
	dup2(pip->outfile, STDOUT_FILENO);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[1]);
	close(pip->infile);
	close(pip->outfile);
	close(pipe_fds[0]);
	if (execute(pip, argv[3], envs) == -1)
		return (-1);
	return (0);
}

static int	run_pipex(t_pip *pip, char **argv, char **envs, int	*pipe_fds)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pid1 = fork();
	if (pid1 < 0)
		ft_error(pip, 2);
	if (pid1 == 0)
	{
		if (run_child(pip, argv, pipe_fds, envs) == -1)
			ft_error(pip, -1);
	}
	pid2 = fork();
	if (pid1 < 0)
		ft_error(pip, 2);
	if (pid2 == 0)
	{
		if (run_parent(pip, argv, pipe_fds, envs) == -1)
			ft_error(pip, -1);
	}
	waitpid(pid1, &status, 0);
	return (status);
}

int	main(int argc, char *argv[], char **envs)
{
	int		status;
	int		pipe_fds[2];
	t_pip	*pip;

	if (argc != 5)
		ft_error(NULL, 0);
	pip = init_pipex();
	if (init_files(pip, argv) == -1)
		ft_error(pip, -1);
	if (pipe(pipe_fds) == -1)
		ft_error(pip, -1);
	status = run_pipex(pip, argv, envs, pipe_fds);
	free_pip(pip);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(0, &status, 0);
	exit(status);
}
