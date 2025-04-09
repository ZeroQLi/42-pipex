/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:30:10 by mtangalv          #+#    #+#             */
/*   Updated: 2025/04/10 00:51:34 by zeroql           ###   ########.fr       */
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
	char	*arg;
	int		in_fd;
	int		out_fd;
	int		invalid_infile;
} t_pip;

void	ft_error(t_pip *pip, int errno);
t_pip	*init_pipex(void);
int		open_infile(t_pip *pip, char *file);
int		open_outfile(char *file);

#endif