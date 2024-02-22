/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:59:56 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/22 20:01:49 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	fill_line(t_mini *mini, int pipe_line)
{
	t_list_parse	*current;
	int				line_size;
	int				i;

	line_size = get_line_size(mini, pipe_line);
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

void	open_heredocs(t_mini *mini, int pipeline)
{
	t_list_parse	*curr;
	int				heredocfd;

	curr = get_pipe_line(mini->lst, pipeline);
	while (curr && curr->flag != PIPE)
	{
		if (curr->flag == HEREDOC)
		{
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
		i++;
	}
	set_fds(mini);
	return (1);
}
