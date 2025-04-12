/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:18:15 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/12 16:47:44 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int execute(t_pip *pip, char *cmd, char **envs)
{
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

static int run_child(t_pip *pip, char *argv[], int *pipe_fds, char **envs)
{
	dup2(pip->infile, STDIN_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[0]);
	close(pip->infile);
	close(pip->outfile);
	close(pipe_fds[1]);
	execute(pip, argv[2], envs);
	return (0);
}

static int run_parent(t_pip *pip, char *argv[], int	*pipe_fds, char **envs)
{
	dup2(pip->outfile, STDOUT_FILENO);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[1]);
	close(pip->infile);
	close(pip->outfile);
	close(pipe_fds[0]);
	execute(pip, argv[3], envs);
	return (0);
}

int	main(int argc, char *argv[], char **envs)
{
	pid_t	pid1;
	pid_t	pid2;
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
	pid1 = fork();
	if (pid1 == -1)
		ft_error(pip, -1);
	if (pid1 == 0)
	{
		if (run_child(pip, argv, pipe_fds, envs) == -1)
			ft_error(pip, -1);
	}
	waitpid(pid1, &status, 0);
	pid2 = fork();
	if (pid2 == -1)
		ft_error(pip, -1);
	if (pid2 == 0)
	{
		if (run_parent(pip, argv, pipe_fds, envs) == -1)
			ft_error(pip, -1);
	}
	waitpid(pid2, &status, 0);
	free_pip(pip);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	exit(0);
}