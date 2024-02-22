/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:59:56 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/22 19:28:02 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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
			outfd = open_out(current);
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
			heredoc_fd = here_doc(mini, current->next);
			if (mini->exit_status == 7)
				return (heredoc_fd);
		}
		current = current->next;
	}
	return (final_check(mini, redin, heredoc_fd, pipe_line));
}

void	fill_fds(t_mini *mini, int pipe_line)
{
	mini->table[pipe_line].infd = get_infd(mini, pipe_line);
	if (mini->exit_status == 7)
	{
		closefds(mini);
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
		mini->table[pipe_line].infd = -2;
		if (current->flag == COMMAND || current->flag == ARG)
			mini->table[pipe_line].line[i++] = current->str;
		if (current->flag == REDIN || current->flag == HEREDOC)
			mini->table[pipe_line].redin = current;
		else if (current->flag == REDOUT || current->flag == APPEND)
			mini->table[pipe_line].redout = current;
		current = current->next;
	}
	mini->table[pipe_line].line[i] = NULL;
	return (1);
}

void a(t_list_parse *lst)
{
	while (lst)
	{
		printf("{%s}", lst->str);
		lst = lst->next;
	}
	printf("\n");
}

void	open_heredocs(t_mini *mini, int pipeline)
{
	t_list_parse	*curr;
	int				heredocfd;

	curr = get_pipe_line(mini->lst, pipeline);
	while (curr && curr->flag != PIPE)
	{
		if (curr->flag == HEREDOC)
		{
			a(mini->lst);
			printf("%s\n", curr->next->str);
			heredocfd = here_doc(mini, curr->next);
			if (curr == mini->table[pipeline].redin)
				mini->table[pipeline].infd = heredocfd;
			else
				close(heredocfd);
		}
		curr = curr->next;
	}
}

int	command_table(t_mini *mini)
{
	int		i;

	mini->table_size = get_table_size(mini->lst);
	mini->table = malloc(sizeof(t_table) * mini->table_size);
	if (!mini->table)
		return (0);
	i = 0;
	while (i < mini->table_size)
	{
		mini->table[i].redin = NULL;
		mini->table[i].redout = NULL;
		if (!fill_line(mini, i))
			return (0);
		open_heredocs(mini, i);
		// fill_fds(mini, i);
		i++;
	}
	set_fds(mini);
	return (1);
}
