/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:35:24 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/22 23:35:01 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	closefds(t_mini *mini)
{
	int			i;

	i = 0;
	while (i < mini->table_size)
	{
		if (mini->table[i].infd > 2)
			close(mini->table[i].infd);
		if (mini->table[i].outfd > 2)
			close(mini->table[i].outfd);
		i++;
	}
}

int	get_table_size(t_list_parse *lst)
{
	int				pipe_lines;
	t_list_parse	*current;

	pipe_lines = 1;
	current = lst;
	while (current)
	{
		if (current->flag == PIPE)
			pipe_lines++;
		current = current->next;
	}
	return (pipe_lines);
}

int	get_line_size(t_mini *mini, int pipe_line)
{
	t_list_parse	*current;
	int				i;
	int				size;

	i = 0;
	current = get_pipe_line(mini->lst, pipe_line);
	size = 0;
	while (current && current->flag != PIPE)
	{
		mini->table[pipe_line].infd = -2;
		mini->table[pipe_line].outfd = -2;
		if (current->flag == COMMAND || current->flag == ARG)
			size++;
		if (current->flag == REDIN || current->flag == HEREDOC)
			mini->table[pipe_line].redin = current;
		else if (current->flag == REDOUT || current->flag == APPEND)
			mini->table[pipe_line].redout = current;
		current = current->next;
	}
	return (size);
}
