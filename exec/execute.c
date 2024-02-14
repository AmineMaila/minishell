/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:24:17 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/14 15:44:30 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

// void	print_open_file_descriptors(void)
// {
//     int max_fd = getdtablesize(); // Get the maximum number of file descriptors
//     printf("Open file descriptors:\n");
//     for (int fd = 0; fd < max_fd; fd++) {
//         if (fcntl(fd, F_GETFD) != -1 || errno != EBADF) { // Check if the file descriptor is valid
//             printf("----[%d]----\n", fd);
//         }
//     }
// }

void	exec_cmd(t_data *pipex, t_cmd_table table)
{
	if (table.infd == -1 || table.outfd == -1 || !table.line[0])
		exit(1);
	if (dup2(table.infd, 0) == -1)
		ft_exit(NULL, NULL, errno);
	close (table.infd);
	if (dup2(table.outfd, 1) == -1)
		ft_exit(NULL, NULL, errno);
	close(table.outfd);
	
	if (exec_builtin(table.line, pipex->env))
		exit(0);
	is_cmd(&table.line[0], *pipex->env);
	if (access(table.line[0], F_OK))
		ft_exit(table.line[0], ": command not found", 1);
	if (execve(table.line[0], table.line, *pipex->env) == -1)
		ft_exit(NULL, NULL, errno);
}

void	birth(t_data *pipex, t_cmd_table table)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit(NULL, NULL, errno);
	if (table.outfd == -42)
		table.outfd = fd[1];
	else
		close(fd[1]);
	pipex->pids[pipex->id_count] = fork();
	if (pipex->pids[pipex->id_count] == -1)
		ft_exit(NULL, NULL, errno);
	if (pipex->pids[pipex->id_count] == 0)
	{
		close(fd[0]);
		exec_cmd(pipex, table);
	}
	pipex->id_count++;
	close(table.infd);
	if (pipex->infd == -42)
		pipex->infd = fd[0];
	else
		close(fd[0]);
	close(table.outfd);
}

void	wait_child(t_data *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->id_count)
	{
		if (waitpid(pipex->pids[i++], &status, 0) == -1)
			ft_exit(NULL, NULL, errno);
	}
	free(pipex->pids);
}

void	spawn_children(t_cmd_table *table, t_data *pipex, int size)
{
	int			fd[2];
	int			i;

	i = 0;
	while (i < size)
	{
		table[i].infd = pipex->infd;
		if (i != size - 1)
			pipex->infd = table[i + 1].infd;
		if (!table[i].line[0])
		{
			if (pipex->infd == -42)
			{
				if (pipe(fd) == -1)
					ft_exit(NULL, NULL, errno);
				pipex->infd = fd[0];
				close(fd[1]);
			}
			close(table[i].infd);
			close(table[i].outfd);
		}
		else
			birth(pipex, table[i]);
		i++;
	}
}

void	execute(t_cmd_table *table, char ***env, int size)
{
	t_data		pipex;

	pipex.env = env;
	pipex.id_count = 0;
	pipex.heredoc = 0;
	pipex.infd = table[0].infd;
	pipex.pids = malloc(size * sizeof(int));
	if (table[0].line[0] && size == 1 && exec_parent(table[0].line, pipex.env))
		return ;
	spawn_children(table, &pipex, size);
	wait_child(&pipex);
}
