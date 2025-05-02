/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:05:30 by mtangalv          #+#    #+#             */
/*   Updated: 2025/05/01 20:53:32 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_env(char *name, char **envs)
{
	int	i;

	i = 0;
	ft_strlen(name);
	while (envs[i])
	{
		if (ft_strnstr(envs[i], name, ft_strlen(name)))
		{
			while (envs[i][0] != '=')
				(envs[i])++;
			(envs[i])++;
			return (envs[i]);
		}
		i++;
	}
	return (NULL);
}

static char	*get_path(char *command, char **envs)
{
	char	**env;
	char	*tmp;
	char	*fullcmd;
	int		i;

	i = 0;
	tmp = get_env("PATH", envs);
	if (tmp == NULL)
		return (NULL);
	env = ft_split(tmp, ':');
	while (env[i])
	{
		tmp = ft_strjoin(env[i++], "/");
		fullcmd = ft_strjoin(tmp, command);
		free(tmp);
		tmp = NULL;
		if (access(fullcmd, F_OK | X_OK) == 0)
			return (free_split(env), fullcmd);
		free(fullcmd);
		fullcmd = NULL;
	}
	return (free_split(env), command);
}

static char	*get_path_free(char *cmd, char **envs)
{
	char	*duped;

	duped = get_path(cmd, envs);
	if (duped == NULL)
	{
		free(cmd);
		cmd = NULL;
	}
	return (duped);
}

int	parse_commands(t_pip *pip, char *command, char **envs)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(command, ' ');
	if (cmds[0] == NULL)
	{
		free(cmds);
		cmds = NULL;
		ft_error(pip, 3);
	}
	if (ft_strchr(cmds[0], '/'))
	{
		pip->args = cmds;
		pip->cmd = ft_strdup(cmds[0]);
		return (0);
	}
	path = get_path_free(ft_strdup(cmds[0]), envs);
	if (path == NULL)
	{
		free_split(cmds);
		ft_error(pip, 3);
	}
	pip->args = cmds;
	pip->cmd = path;
	return (0);
}
