/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:30:10 by mtangalv          #+#    #+#             */
/*   Updated: 2025/04/11 22:55:05 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "../libft/libft.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// REMOVE
#include <stdio.h>

#define INVALID_FILE ".pipex_err"

typedef struct s_pip
{
	char	*cmd;
	char	**args;
	int		infile;
	int		outfile;
	int		invalid_infile;
} t_pip;

void	ft_error(t_pip *pip, int errno);
void	free_split(char **sploit);
void	free_pip(t_pip *pip);
t_pip	*init_pipex(void);
int		open_infile(t_pip *pip, char *file);
int		open_outfile(char *file);
int		init_files(t_pip *pip, char *argv[]);
int		init_pipe(t_pip *pip);
int		parse_commands(t_pip *pip, char *command, char **envs);

#endif