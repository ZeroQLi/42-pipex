/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeroql <zeroql@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:18:15 by zeroql            #+#    #+#             */
/*   Updated: 2025/04/09 10:54:21 by zeroql           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int	argc, char *argv[])
{
	// int	pipe_fds[2];
	// pid_t	pid;

	if (argc != 5)
		ft_error(0);
	check_file(argv[1], 0);
	ft_printf("%s\n", argv[0]);
	return (0);
}