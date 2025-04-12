/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:33:13 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/12 23:48:50 by zeroql           ###   ########.fr       */
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
	env = ft_split(get_env("PATH", envs), ':');
	while (env[i])
	{
		tmp = ft_strjoin(env[i], "/");
		fullcmd = ft_strjoin(tmp, command);
		free(tmp);
		tmp = NULL;
		if (access(fullcmd, F_OK | X_OK) == 0)
		{
			free_split(env);
			return (fullcmd);
		}
		free(fullcmd);
		fullcmd = NULL;
		i++;
	}
	free_split(env);
	return (command);
}

int	parse_commands(t_pip *pip, char *command, char **envs)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(command, ' ');
	path = get_path(cmds[0], envs);
	pip->cmd = path;
	pip->args = cmds;
	return (0);
}
