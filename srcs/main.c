/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:55:55 by amiguez           #+#    #+#             */
/*   Updated: 2022/05/18 23:26:47 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipe	data;

	if (argc != 5)
		ft_error("Usage : ./pipex <infile> <cmd1> <cmd2> <outfile>");
	parsing(argc, argv, env, &data);
	printf("execve(%s, %s)\n", data.path[0], *data.cmd[0]);
	execve (data.path[0], data.cmd[0], env);
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
