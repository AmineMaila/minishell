/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:24:17 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/21 21:40:23 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	exec_cmd(t_table table, t_mini *mini)
{
	if (table.infd == -1 || table.outfd == -1 || !table.line[0])
	{
		ft_exit(mini, NULL, NULL, 0);
		exit(1);
	}
	if (dup2(table.infd, 0) == -1)
		ft_exit(mini, NULL, NULL, errno);
	close (table.infd);
	if (dup2(table.outfd, 1) == -1)
		ft_exit(mini, NULL, NULL, errno);
	close(table.outfd);
	if (exec_builtin(mini, table.line) != -1)
		(ft_exit(mini, NULL, NULL, 0), exit(mini->exit_status));
	is_cmd(mini, &table.line[0], mini->env);
	if (access(table.line[0], F_OK))
		ft_exit(mini, table.line[0], "command not found", 127);
	if (execve(table.line[0], table.line, mini->env) == -1)
		ft_exit(mini, NULL, NULL, 126);
}

void	birth(t_mini *mini, t_data *pipex, t_table table)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit(mini, NULL, NULL, errno);
	if (table.outfd == -42)
		table.outfd = fd[1];
	else
		close(fd[1]);
	mini->pids[pipex->id_count] = fork();
	if (mini->pids[pipex->id_count] == -1)
		ft_exit(mini, NULL, NULL, errno);
	if (mini->pids[pipex->id_count] == 0)
	{
		close(fd[0]);
		exec_cmd(table, mini);
	}
	pipex->id_count++;
	close(table.infd);
	if (pipex->infd == -42)
		pipex->infd = fd[0];
	else
		close(fd[0]);
	close(table.outfd);
}

int	wait_child(t_data *pipex, t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->id_count)
	{
		if (waitpid(mini->pids[i++], &status, 0) == -1)
			ft_exit(mini, NULL, NULL, errno);
	}
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (status == 2)
			write(1, "\n", 1);
		mini->exit_status = status + 128;
	}
	return (1);
}

void	spawn_children(t_mini *mini, t_data *pipex)
{
	int			fd[2];
	int			i;

	i = 0;
	while (i < mini->table_size)
	{
		mini->table[i].infd = pipex->infd;
		if (i != mini->table_size - 1)
			pipex->infd = mini->table[i + 1].infd;
		if (!mini->table[i].line[0])
		{
			if (pipex->infd == -42)
			{
				if (pipe(fd) == -1)
					ft_exit(mini, NULL, NULL, errno);
				pipex->infd = fd[0];
				close(fd[1]);
			}
			close(mini->table[i].infd);
			close(mini->table[i].outfd);
		}
		else
			birth(mini, pipex, mini->table[i]);
		i++;
	}
}

int	execute(t_mini *mini)
{
	t_data		pipex;
	int			execp;

	pipex.id_count = 0;
	pipex.heredoc = 0;
	pipex.infd = mini->table[0].infd;
	mini->pids = malloc(mini->table_size * sizeof(int));
	if (!mini->pids)
		ft_exit(mini, NULL, NULL, ENOMEM);
	if (mini->table[0].line[0] && mini->table_size == 1)
	{
		execp = exec_parent(mini, mini->table[0].line);
		if (execp != -1)
			return (execp);
	}
	spawn_children(mini, &pipex);
	wait_child(&pipex, mini);
	return (0);
}
