/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:24:17 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/12 20:12:55 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_open_file_descriptors(void)
{
    int max_fd = getdtablesize(); // Get the maximum number of file descriptors
    printf("Open file descriptors:\n");
    for (int fd = 0; fd < max_fd; fd++) {
        if (fcntl(fd, F_GETFD) != -1 || errno != EBADF) { // Check if the file descriptor is valid
            printf("----[%d]----\n", fd);
        }
    }
}

void	exec_cmd(t_data *pipex, t_cmd_table table)
{
	if (table.infd == -1 || table.outfd == -1 || !table.line[0])
		exit(0);
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
	pipex->pids[pipex->id_count] = fork();
	if (pipex->pids[pipex->id_count] == -1)
		ft_exit(NULL, NULL, errno);
	if (pipex->pids[pipex->id_count] == 0)
		exec_cmd(pipex, table);
	pipex->id_count++;
	close(table.infd);
	close(table.outfd);
}

void	wait_child(t_data *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->id_count)
		if (waitpid(pipex->pids[i++], 0, 0) == -1)
			ft_exit(NULL, NULL, errno);
	free(pipex->pids);
}

int	exec_parent(char **line, char ***env)
{
	if (!ft_strcmp("unset", line[0]))
		return (unset(line, env), 1);
	else if (!ft_strcmp("export", line[0]))
		return (export(line, env), 1);
	else if(!ft_strcmp("cd", line[0]))
		return(cd(line[1], *env), 1);
	return (0);
}

void	execute(t_cmd_table *table, char ***env, int size)
{
	t_data	pipex;
	int		i;

	pipex.env = env;
	pipex.id_count = 0;
	pipex.heredoc = 0;
	pipex.pids = malloc(size * sizeof(int));
	i = 0;
	while (i < size)
	{
		if (!table[i].line[0] || exec_parent(table[i].line, env))
		{
			close(table[i].infd);
			close(table[i].outfd);
		}
		else
			birth(&pipex, table[i]);
		i++;
	}
	wait_child(&pipex);
	// print_open_file_descriptors();
}
