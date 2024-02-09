/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:24:17 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/09 22:53:32 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	out_fd(t_data *pipex, int out, int fd)
{
	if (out > 2)
	{
		pipex->outfd = out;
		close(fd);
	}
	else
		pipex->outfd = fd;
}

void	exec_cmd(t_data *pipex, t_cmd_table table)
{
	if (pipex->infd == -1 || pipex->outfd == -1)
		exit(0);
	if (dup2(pipex->infd, 0) == -1)
		ft_exit(NULL, NULL, errno);
	close (pipex->infd);
	if (dup2(pipex->outfd, 1) == -1)
		ft_exit(NULL, NULL, errno);
	close(pipex->outfd);
	if (access(table.line[0], F_OK))
		ft_exit(table.line[0], ": command not found", 1);
	if (execve(table.line[0], table.line, NULL) == -1)
		ft_exit(NULL, NULL, errno);
}

void	birth(t_data *pipex, t_cmd_table table, int table_fd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit(NULL, NULL, errno);
	out_fd(pipex, table.outfd, fd[1]);
	pipex->pids[pipex->id_count] = fork();
	if (pipex->pids[pipex->id_count] == -1)
		ft_exit(NULL, NULL, errno);
	if (pipex->pids[pipex->id_count] == 0)
	{
		close(fd[0]);
		if (pipex->outfd != fd[1])
			close(fd[1]);
		exec_cmd(pipex, table);
	}
	pipex->id_count++;
	close(pipex->infd);
	if (table_fd > 2)
		(pipex->infd = table_fd, close(fd[0]));
	else if (table_fd == -42)
		pipex->infd = fd[0];
	if (pipex->outfd != fd[1])
		close(fd[1]);
	close(pipex->outfd);
}

void	spawn_children(t_data *pipex, t_cmd_table *table, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (table[i].line[0])
			birth(pipex, table[i], table[i + 1].infd);
		else if (table[i + 1].infd > 2)
			pipex->infd = table[i + 1].infd;
		i++;
	}
	pipex->outfd = table[i].outfd;
	pipex->pids[pipex->id_count] = fork();
	if (pipex->pids[pipex->id_count] == -1)
		ft_exit(NULL, NULL, errno);
	if (pipex->pids[pipex->id_count] == 0)
		exec_cmd(pipex, table[i]);
	pipex->id_count++;
	close(pipex->infd);
	close(pipex->outfd);
	i = 0;
	while (i < pipex->id_count)
		if (waitpid(pipex->pids[i++], 0, 0) == -1)
			ft_exit(NULL, NULL, errno);
	free(pipex->pids);
}

void	execute(t_cmd_table *table, int size)
{
	t_data	pipex;

	pipex.id_count = 0;
	pipex.heredoc = 0;
	pipex.pids = malloc(size * sizeof(int));
	pipex.infd = table[0].infd;
	spawn_children(&pipex, table, size);
}