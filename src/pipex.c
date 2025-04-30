/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:05:48 by mtangalv          #+#    #+#             */
/*   Updated: 2025/04/30 12:23:20 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	execute(t_pip *pip, char *cmd, char **envs)
{
	if (!cmd[0])
		ft_error(pip, 1);
	if (parse_commands(pip, cmd, envs) == -1)
		return (-1);
	execve(pip->cmd, pip->args, envs);
	ft_error(pip, 3);
	return (0);
}

static int	run_child(t_pip *pip, char *argv[], int *pipe_fds, char **envs)
{
	close(pipe_fds[0]);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		ft_error(pip, -1);
	close(pipe_fds[1]);
	pip->infile = open_infile(argv[1]);
	if (pip->infile == -1)
		ft_error(pip, 8218);
	if (dup2(pip->infile, STDIN_FILENO) == -1)
		ft_error(pip, -1);
	close(pip->infile);
	pip->infile = -1;
	if (execute(pip, argv[2], envs) == -1)
		return (-1);
	return (0);
}

static int	run_parent(t_pip *pip, char *argv[], int *pipe_fds, char **envs)
{
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		ft_error(pip, -1);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	pip->outfile = open_outfile(argv[4]);
	if (pip->outfile == -1)
		ft_error(pip, 8218);
	if (dup2(pip->outfile, STDOUT_FILENO) == -1)
		ft_error(pip, -1);
	close(pip->outfile);
	pip->outfile = -1;
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
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid2, &status, 0);
	wait(NULL);
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
	if (pipe(pipe_fds) == -1)
		ft_error(pip, -1);
	status = run_pipex(pip, argv, envs, pipe_fds);
	free_pip(pip);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit(WTERMSIG(status) + 128);
	exit(0);
}
