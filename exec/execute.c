/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:24:17 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/16 15:38:19 by mmaila           ###   ########.fr       */
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

void	exec_cmd(t_cmd_table table, t_minishell *minishell)
{
	if (table.infd == -1 || table.outfd == -1 || !table.line[0])
		exit(1);
	if (dup2(table.infd, 0) == -1)
		cleanup(minishell, errno);
	close (table.infd);
	if (dup2(table.outfd, 1) == -1)
		cleanup(minishell, errno);
	close(table.outfd);
	if (exec_builtin(table.line, &minishell->env))
		exit(0);
	is_cmd(&table.line[0], minishell->env);
	if (access(table.line[0], F_OK))
		ft_exit(table.line[0], ": command not found", 1);
	if (execve(table.line[0], table.line, minishell->env) == -1)
		cleanup(minishell, errno);
}

void	birth(t_minishell *minishell, t_data *pipex, t_cmd_table table)
{
	int	fd[2];

	if (pipe(fd) == -1)
		cleanup(minishell, errno);
	if (table.outfd == -42)
		table.outfd = fd[1];
	else
		close(fd[1]);
	pipex->pids[pipex->id_count] = fork();
	if (pipex->pids[pipex->id_count] == -1)
		cleanup(minishell, errno);
	if (pipex->pids[pipex->id_count] == 0)
	{
		close(fd[0]);
		exec_cmd(table, minishell);
	}
	pipex->id_count++;
	close(table.infd);
	if (pipex->infd == -42)
		pipex->infd = fd[0];
	else
		close(fd[0]);
	close(table.outfd);
}

int	wait_child(t_data *pipex, t_minishell *minishell)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->id_count)
	{
		if (waitpid(pipex->pids[i++], &status, 0) == -1)
		{
			free(pipex->pids);
			cleanup(minishell, errno);
		}
	}
	free(pipex->pids);
	if (WIFSIGNALED(status))
	{
		// if (status == SIGSEGV)
		// 	printf("Segmentation fault: %d\n", status);
		// else if (status == SIGABRT)
		// 	printf("Abort: %d\n", status);
		// else if (status == SIGBUS)
		// 	printf("Bus error: %d\n", status);
		return (status + 128);
	}
	return (WEXITSTATUS(status));
}

void	spawn_children(t_minishell *minishell, t_data *pipex)
{
	int			fd[2];
	int			i;

	i = 0;
	while (i < minishell->cmd_table_size)
	{
		minishell->cmd_table[i].infd = pipex->infd;
		if (i != minishell->cmd_table_size - 1)
			pipex->infd = minishell->cmd_table[i + 1].infd;
		if (!minishell->cmd_table[i].line[0])
		{
			if (pipex->infd == -42)
			{
				if (pipe(fd) == -1)
					cleanup(minishell, errno);
				pipex->infd = fd[0];
				close(fd[1]);
			}
			close(minishell->cmd_table[i].infd);
			close(minishell->cmd_table[i].outfd);
		}
		else
			birth(minishell, pipex, minishell->cmd_table[i]);
		i++;
	}
}

int	execute(t_minishell *minishell)
{
	t_data		pipex;

	pipex.id_count = 0;
	pipex.heredoc = 0;
	pipex.infd = minishell->cmd_table[0].infd;
	pipex.pids = malloc(minishell->cmd_table_size * sizeof(int));
	if (!pipex.pids)
		cleanup(minishell, errno);
	if (minishell->cmd_table[0].line[0] && minishell->cmd_table_size == 1
		&& exec_parent(minishell->cmd_table[0].line, &minishell->env))
		return (0);
	spawn_children(minishell, &pipex);
	return (wait_child(&pipex, minishell));
}
