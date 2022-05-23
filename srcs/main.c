/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:55:55 by amiguez           #+#    #+#             */
/*   Updated: 2022/05/23 18:47:45 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipe	data;

	parsing(argc, argv, env, &data);
	pipe(data.pipe);
	chek_pipe(data);
	ft_first_proc(&data, env, argv[1]);
	if (close (data.pipe[1]) == -1)
		ft_error("Error : Close failed");
	ft_second_proc(&data, env, argv[4]);
	waitpid(data.pid[1], 0, 0);
	unlink("4");
	unlink("3");
	if (close(data.pipe[0]) == -1)
		ft_error("Error: Close failed");
	waitpid(data.pid[0], 0, 0);
	ft_leave(data);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(0);
}

void	ft_first_proc(t_pipe *data, char **env, char *infile)
{
	int		fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("zsh: no such file or directory: %s\n", infile);
		return ;
	}
	data->pid[0] = fork();
	if (data->pid[0] == 0)
	{
		if (close (data->pipe[0]) < 0)
			ft_error("Error: Close failed");
		if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
			ft_error("Error: Dup2 failed");
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_error("Error: Dup2 failed");
		execve (data->path[0], data->cmd[0], env);
		ft_error("Error: Execve 1 failed");
	}
	close(fd);
}

void	ft_second_proc(t_pipe *data, char **env, char *outfile)
{
	int		fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		ft_error("Error: Open failed");
	data->pid[1] = fork();
	if (data->pid[1] == 0)
	{	
		if (close(data->pipe[1] == -1))
			ft_error("Error: Close failed");
		if (dup2(data->pipe[0], STDIN_FILENO) == -1)
			ft_error("Error: Dup2 failed");
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_error("Error: Dup2 failed");
		execve (data->path[1], data->cmd[1], env);
		ft_error("Error: Execve 2 failed");
	}
	close(fd);
}

void	ft_leave(t_pipe data)
{
	free(data.path[0]);
	free(data.path[1]);
	free(data.cmd[0][0]);
	free(data.cmd[0][1]);
	free(data.cmd[1][0]);
	free(data.cmd[1][1]);
	exit(0);
}
