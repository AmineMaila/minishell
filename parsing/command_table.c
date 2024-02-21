/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:59:56 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/21 12:32:27 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	open_out(t_list_parse	*redout, char *outfile)
{
	int	outfd;

	if (redout->flag == REDOUT)
	{
		outfd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
			outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
			print_error(outfile, NULL);
		return (outfd);
	}
	else
	{
		outfd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (outfd == -1)
			outfd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfd == -1)
			print_error(outfile, NULL);
		return (outfd);
	}
}

int	get_outfd(t_mini *mini, int pipe_line)
{
	t_list_parse	*current;
	int				outfd;

	outfd = -2;
	current = get_pipe_line(mini->lst, pipe_line);
	while (current && current->flag != PIPE)
	{
		if (current->flag == REDOUT || current->flag == APPEND)
		{
			close(outfd);
			outfd = open_out(current, current->next->str);
		}
		current = current->next;
	}
	if (outfd == -2)
	{
		if (pipe_line == mini->table_size - 1)
			return (open("/dev/stdout", O_RDONLY));
		return (-42);
	}
	return (outfd);
}

int	get_infd(t_mini *mini, int pipe_line)
{
	t_list_parse	*current;
	t_list_parse	*redin;
	int				heredoc_fd;

	redin = NULL;
	heredoc_fd = -1;
	current = get_pipe_line(mini->lst, pipe_line);
	while (current && current->flag != PIPE)
	{
		if (current->flag == REDIN || current->flag == HEREDOC)
			redin = current;
		if (current->flag == HEREDOC)
		{
			close(heredoc_fd);
			heredoc_fd = here_doc(mini, current->next->str);
			if (mini->exit_status == 7)
				return (heredoc_fd);
		}
		current = current->next;
	}
	if (!redin)
	{
		if (pipe_line == 0)
			return (open("/dev/stdin", O_RDONLY));
		return (-42);
	}
	if (redin->flag == HEREDOC)
	{
		if (open_redins(mini, pipe_line) == -1)
			return (-1);
		return (heredoc_fd);
	}
	return (close(heredoc_fd), open_redins(mini, pipe_line));
}

void	fill_fds(t_mini *mini, int pipe_line)
{
	int	i;

	i = 0;
	mini->table[pipe_line].infd = get_infd(mini, pipe_line);
	if (mini->exit_status == 7)
	{
		while (i < mini->table_size)
			close(mini->table[i++].infd);
		return ;
	}
	mini->table[pipe_line].outfd = get_outfd(mini, pipe_line);
}

int	fill_line(t_mini *mini, int pipe_line)
{
	t_list_parse	*current;
	int				line_size;
	int				i;

	line_size = get_line_size(mini->lst, pipe_line);
	mini->table[pipe_line].line
		= malloc(sizeof(char *) * (line_size + 1));
	if (!mini->table[pipe_line].line)
		return (0);
	current = get_pipe_line(mini->lst, pipe_line);
	i = 0;
	while (i < line_size)
	{
		if (current->flag == COMMAND || current->flag == ARG)
			mini->table[pipe_line].line[i++] = current->str;
		current = current->next;
	}
	mini->table[pipe_line].line[i] = NULL;
	return (1);
}

int	command_table(t_mini *mini)
{
	int	i;
	
	mini->table_size = get_table_size(mini->lst);
	mini->table = malloc(sizeof(t_table) * mini->table_size);
	if (!mini->table)
		return (0);
	i = 0;
	while (i < mini->table_size)
	{
		if (!fill_line(mini, i))
			return (0);
		fill_fds(mini, i);
		i++;
	}
	return (1);
}
