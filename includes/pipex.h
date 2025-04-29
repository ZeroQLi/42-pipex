/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:30:10 by mtangalv          #+#    #+#             */
/*   Updated: 2025/04/27 17:06:43 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pip
{
	char	*cmd;
	char	**args;
	int		infile;
	int		outfile;
}	t_pip;

t_pip	*init_pipex(void);
int		open_outfile(char *file);
int		open_infile(char *file);
int		parse_commands(t_pip *pip, char *command, char **envs);
void	ft_error(t_pip *pip, int errno);
void	free_pip(t_pip *pip);
void	free_split(char **sploit);
#endif